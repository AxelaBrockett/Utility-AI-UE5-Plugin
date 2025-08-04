// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionRequirements/UtilityActionRequirementSenseVal.h"

#include "AIController.h"
#include "Components/UtilityComponent.h"
#include "Engine/World.h"
#include "Helpers/UtilityHelpers.h"
#include "MassActorSubsystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense.h"
#include "VisualLogger/VisualLogger.h"

namespace Utility::Requirements
{
	bool CompareValues(const float Left, const float Right, const EGenericAICheck& ComparisonType)
	{
		switch (ComparisonType)
		{
			case (EGenericAICheck::Equal):
			{
				return Left == Right;
				break;
			}
			case (EGenericAICheck::NotEqual):
			{
				return Left != Right;
				break;
			}
			case (EGenericAICheck::Less):
			{
				return Left < Right;
				break;
			}
			case (EGenericAICheck::LessOrEqual):
			{
				return Left <= Right;
				break;
			}
			case (EGenericAICheck::Greater):
			{
				return Left > Right;
				break;
			}
			case (EGenericAICheck::GreaterOrEqual):
			{
				return Left >= Right;
				break;
			}
			default:
			{
				ensureAlwaysMsgf(false, TEXT("Unhandled Comparison Type [ %d ]."), ComparisonType);
				return false;
				break;
			}
		}
	}
}

const bool UUtilityActionRequirementSenseVal::CheckRequirement(UUtilityComponent& OwnerComp) const
{
	const AAIController* const AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController))
	{
		UE_VLOG_ALWAYS_UELOG(
			OwnerComp.GetOwner(),
			LogUtility,
			Warning,
			TEXT("%s - Utility Component [ %s ] is owned by [ %s ] - expected type of AAIController."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*OwnerComp.GetName(),
			*OwnerComp.GetOwner()->GetName()
		);
		return false;
	}

	return IsSenseValueAboveMinimum(*AIController);
}

const bool UUtilityActionRequirementSenseVal::CheckRequirement(const FMassEntityHandle& Entity) const
{
	const UWorld* const World = GetWorld();
	if (!IsValid(World))
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Error,
			TEXT("%s - Invalid world."),
			ANSI_TO_TCHAR(__FUNCTION__)
		);
		return false;
	}

	// This version of CheckRequirement() could be overridden to check fragment values if perception fragments are created and used
	const UMassActorSubsystem* const MassActorSubsystem = World->GetSubsystem<UMassActorSubsystem>();
	if (!IsValid(MassActorSubsystem))
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Warning,
			TEXT("%s - World [ %s ] has no valid Mass Actor Subsystem."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*World->GetName()
		);
		return false;
	}

	const APawn* const AIPawn = Cast<APawn>(MassActorSubsystem->GetActorFromHandle(Entity));
	if (!IsValid(AIPawn))
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Warning,
			TEXT("%s - Mass Actor Subsystem could not get valid Pawn for entity [ index [ %i ] serial number [ %i ]]."),
			ANSI_TO_TCHAR(__FUNCTION__),
			Entity.Index,
			Entity.SerialNumber
		);
		return false;
	}

	const AAIController* const AIController = Cast<AAIController>(AIPawn->GetController());
	if (!IsValid(AIController))
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Warning,
			TEXT("%s - Pawn [ %s ] does not have a valid AI Controller."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*AIPawn->GetName()
		);
		return false;
	}

	return IsSenseValueAboveMinimum(*AIController);
}

const bool UUtilityActionRequirementSenseVal::IsSenseValueAboveMinimum(const AAIController& AIController) const
{
	const UAIPerceptionComponent* const PerceptionComponent = AIController.FindComponentByClass<UAIPerceptionComponent>();
	if (!IsValid(PerceptionComponent))
	{
		UE_VLOG_ALWAYS_UELOG(
			&AIController,
			LogUtility,
			Warning,
			TEXT("%s - AI Controller [ %s ] does not have a valid AI Perception Component."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*AIController.GetName()
		);
		return false;
	}

	const FAISenseID SenseID = UAISense::GetSenseID(SenseToUse);
	UE_CVLOG_ALWAYS_UELOG(
		!SenseID.IsValid(),
		&AIController,
		LogUtility,
		Log,
		TEXT("%s - Sense To Use does not return a valid Sense ID. Will check all other senses."),
		ANSI_TO_TCHAR(__FUNCTION__)
	);

	float HighestStrength = 0.0f;
	for (UAIPerceptionComponent::FActorPerceptionContainer::TConstIterator DataIt = PerceptionComponent->GetPerceptualDataConstIterator(); DataIt; ++DataIt)
	{
		const FActorPerceptionInfo* const ActorInfo = &DataIt->Value;
		if (ActorInfo == nullptr)
		{
			continue;
		}

		const float SenseValue = SenseID.IsValid() ? ActorInfo->LastSensedStimuli[SenseID].Strength : GetHighestStrengthFromStimuli(ActorInfo->LastSensedStimuli);
		HighestStrength = SenseValue > HighestStrength ? SenseValue : HighestStrength;
	}

	return Utility::Requirements::CompareValues(HighestStrength, GoalSenseValue, ValueComparison);
}

const float UUtilityActionRequirementSenseVal::GetHighestStrengthFromStimuli(const TArray<FAIStimulus>& Stimuli) const
{
	float HighestStrength = 0.0f;
	for (const FAIStimulus& Stimulus : Stimuli)
	{
		const float StimulusStrength = Stimulus.Strength;
		HighestStrength = StimulusStrength > HighestStrength ? StimulusStrength : HighestStrength;
	}
	return HighestStrength;
}