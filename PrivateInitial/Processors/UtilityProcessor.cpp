// Fill out your copyright notice in the Description page of Project Settings.

#include "Processors/UtilityProcessor.h"

#include "Actions/UtilityActionBase.h"
#include "DataAssets/UtilityDataAsset.h"
#include "Engine/World.h"
#include "Helpers/UtilityHelpers.h"
#include "MassBehaviorSettings.h"
#include "MassCommonTypes.h"
#include "MassEntityManager.h"
#include "MassEntityQuery.h"
#include "MassEntityTypes.h"
#include "MassExecutionContext.h"
#include "MassLODTypes.h"
#include "MassSignalSubsystem.h"
#include "MassSignalTypes.h"
#include "MassSimulationLOD.h"

namespace UE::MassBehavior
{
	template<typename TFunc>
	void ForEachEntityInChunk(
		FMassExecutionContext& Context,
		TFunc&& Callback)
	{
		const TArrayView<FMassUtilityInstanceFragment> UtilityInstanceList = Context.GetMutableFragmentView<FMassUtilityInstanceFragment>();
		const FMassUtilitySharedFragment& SharedUtilityDataAsset = Context.GetConstSharedFragment<FMassUtilitySharedFragment>();

		const int32 NumEntities = Context.GetNumEntities();
		check(NumEntities > 0);

		const UUtilityDataAsset* UtilityDataAsset = SharedUtilityDataAsset.UtilityDataAsset;

		for (int32 EntityIndex = 0; EntityIndex < NumEntities; EntityIndex++)
		{
			FMassUtilityInstanceFragment& UtilityFragment = UtilityInstanceList[EntityIndex];
			const FMassEntityHandle Entity = Context.GetEntity(EntityIndex);

			Callback(UtilityFragment, Entity);
		}
	}
}

/*
* Utility Activation Processor
*/

UUtilityActivationProcessor::UUtilityActivationProcessor(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), EntityQuery(*this)
{
	ExecutionOrder.ExecuteAfter.Add(UE::Mass::ProcessorGroupNames::LOD);
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Behavior);
	bRequiresGameThreadExecution = true;
}

void UUtilityActivationProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FMassUtilityInstanceFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FMassUtilitySharedFragment>();
	EntityQuery.AddTagRequirement<FMassUtilityActivatedTag>(EMassFragmentPresence::None);
	EntityQuery.AddChunkRequirement<FMassSimulationVariableTickChunkFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::Optional);

	ProcessorRequirements.AddSubsystemRequirement<UMassSignalSubsystem>(EMassFragmentAccess::ReadWrite);
}

void UUtilityActivationProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	const UMassBehaviorSettings* const BehaviorSettings = GetDefault<UMassBehaviorSettings>();
	check(IsValid(BehaviorSettings));

	TArray<FMassEntityHandle> EntitiesToSignal;
	int32 ActivationCounts[EMassLOD::Max]{ 0,0,0,0 };

	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[&EntitiesToSignal, &ActivationCounts, MaxActivationsPerLOD = BehaviorSettings->MaxActivationsPerLOD](FMassExecutionContext& Context)
		{
			const int32 NumEntities = Context.GetNumEntities();
			const EMassLOD::Type ChunkLOD = FMassSimulationVariableTickChunkFragment::GetChunkLOD(Context);
			if (ActivationCounts[ChunkLOD] >= MaxActivationsPerLOD[ChunkLOD])
			{
				return;
			}
			ActivationCounts[ChunkLOD] += NumEntities;

			const TArrayView<FMassUtilityInstanceFragment>& UtilityInstanceFragments = Context.GetMutableFragmentView<FMassUtilityInstanceFragment>();
			const FMassUtilitySharedFragment& SharedUtilityAsset = Context.GetConstSharedFragment<FMassUtilitySharedFragment>();

			if (!IsValid(SharedUtilityAsset.UtilityDataAsset))
			{
				return;
			}

			EntitiesToSignal.Reserve(EntitiesToSignal.Num() + NumEntities);

			for (int32 EntityIndex = 0; EntityIndex < NumEntities; EntityIndex++)
			{
				FMassUtilityInstanceFragment& UtilityFragment = UtilityInstanceFragments[EntityIndex];
				UtilityFragment.UtilityActions = SharedUtilityAsset.UtilityDataAsset->GetActions();
				const FMassEntityHandle& Entity = Context.GetEntity(EntityIndex);
				Context.Defer().AddTag<FMassUtilityActivatedTag>(Entity);
				EntitiesToSignal.Add(Entity);
			}
		}
	);

	if (EntitiesToSignal.Num())
	{
		UMassSignalSubsystem& SignalSubsystem = Context.GetMutableSubsystemChecked<UMassSignalSubsystem>();
		SignalSubsystem.SignalEntities(UE::Mass::Signals::NewUtilityActionRequired, EntitiesToSignal);
	}
}

/*
* Utility Processor
*/

UUtilityProcessor::UUtilityProcessor(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bRequiresGameThreadExecution = true;

	ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::Behavior;

	ExecutionOrder.ExecuteAfter.Add(UE::Mass::ProcessorGroupNames::SyncWorldToMass);
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Tasks);
}

void UUtilityProcessor::Initialize(UObject& Owner)
{
	Super::Initialize(Owner);

	const UWorld* const World = GetWorld();
	check(IsValid(World));

	UMassSignalSubsystem* const MassSignalSubsystem = World->GetSubsystem<UMassSignalSubsystem>();
	check(IsValid(MassSignalSubsystem));

	SubscribeToSignal(*MassSignalSubsystem, UE::Mass::Signals::NewUtilityActionRequired);
}

void UUtilityProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FMassUtilityInstanceFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FMassUtilitySharedFragment>();
	EntityQuery.AddTagRequirement<FMassUtilityActivatedTag>(EMassFragmentPresence::All);

	ProcessorRequirements.AddSubsystemRequirement<UMassSignalSubsystem>(EMassFragmentAccess::ReadWrite);
}

void UUtilityProcessor::SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals)
{
	TArray<FMassEntityHandle> EntitiesToSignal;

	EntityQuery.ForEachEntityChunk(
		EntityManager,
		Context,
		[&EntitiesToSignal, &EntityManager, &EntitySignals](FMassExecutionContext& Context)
		{
			UE::MassBehavior::ForEachEntityInChunk(
				Context,
				[&EntitiesToSignal](FMassUtilityInstanceFragment& UtilityFragment, const FMassEntityHandle& Entity)
				{
					const TArray<TObjectPtr<UUtilityActionBase>>& Actions = UtilityFragment.UtilityActions;

					if (Actions.IsEmpty())
					{
						return;
					}

					TMap<UUtilityActionBase*, const float> PossibleActionsToScores;

					for (UUtilityActionBase* const Action : Actions)
					{
						if (!ensureAlwaysMsgf(IsValid(Action), TEXT("Utility Instance Fragment has invalid action.")))
						{
							continue;
						}
						const float ActionScore = Action->GetActionScore(Entity);
						if (Action->CheckAllRequirements(Entity) && ActionScore > 0.0f)
						{
							PossibleActionsToScores.Add(Action, ActionScore);
						}
					}

					if (PossibleActionsToScores.IsEmpty())
					{
						return;
					}

					PossibleActionsToScores.ValueStableSort([](const float& First, const float& Second) -> bool
						{
							return First > Second;
						}
					);

					EUtilityActionRunStatus ActionStatus = EUtilityActionRunStatus::Failed;
					for (TPair<UUtilityActionBase*, const float>& ActionPair : PossibleActionsToScores)
					{
						ActionStatus = ActionPair.Key->PerformAction(Entity);

						if (ActionStatus != EUtilityActionRunStatus::Failed)
						{
							UtilityFragment.CurrentAction = ActionPair.Key;
							break;
						}
					}

					if (ActionStatus != EUtilityActionRunStatus::Running)
					{
						EntitiesToSignal.Add(Entity);
					}
				}
			);
		}
	);

	if (EntitiesToSignal.Num())
	{
		UMassSignalSubsystem& SignalSubsystem = Context.GetMutableSubsystemChecked<UMassSignalSubsystem>();
		SignalSubsystem.SignalEntities(UE::Mass::Signals::NewUtilityActionRequired, EntitiesToSignal);
	}
}