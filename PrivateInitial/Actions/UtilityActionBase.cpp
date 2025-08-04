// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/UtilityActionBase.h"

#include "Actions/ActionFactors/UtilityActionFactorBase.h"
#include "Actions/ActionRequirements/UtilityActionRequirementBase.h"
#include "Components/UtilityComponent.h"
#include "MassSignalSubsystem.h"
#include "VisualLogger/VisualLogger.h"

/*************************************************
* FUtilityActionTickFunction
*************************************************/

void FUtilityActionTickFunction::ExecuteTick(
	float DeltaTime,
	ELevelTick TickType,
	ENamedThreads::Type CurrentThread,
	const FGraphEventRef& MyCompletionGraphEvent
)
{
	if (IsValid(Action))
	{
		if (TickType != LEVELTICK_ViewportsOnly || Action->ShouldTickIfViewportsOnly())
		{
			FScopeCycleCounterUObject ActionScope(Action);
			Action->TickAction(DeltaTime, TickType, *this);
		}
	}
}

FString FUtilityActionTickFunction::DiagnosticMessage()
{
	return Action->GetFullName() + TEXT("[TickAction]");
}

FName FUtilityActionTickFunction::DiagnosticContext(bool bDetailed)
{
	if (bDetailed)
	{
		// Format is "ActionNativeClass/ActionClass"
		FString ContextString = FString::Printf(TEXT("%s/%s"), *GetParentNativeClass(Action->GetClass())->GetName(), *Action->GetClass()->GetName());
		return FName(*ContextString);
	}
	else
	{
		return GetParentNativeClass(Action->GetClass())->GetFName();
	}
}

/*************************************************
* UUtilityActionBase
*************************************************/

UUtilityActionBase::UUtilityActionBase()
{
	PrimaryUtilityActionTick.bCanEverTick = true;
	PrimaryUtilityActionTick.bStartWithTickEnabled = false;
}

void UUtilityActionBase::BindToRequirementDelegates() const
{
	for (UUtilityActionRequirementBase* const Requirement : Requirements)
	{
		if (!ensureAlwaysMsgf(IsValid(Requirement), TEXT("Utility Action has invalid requirement.")))
		{
			continue;
		}

		Requirement->OnAsyncRequirementCheckedDelegate.AddDynamic(this, &UUtilityActionBase::OnAsyncRequirementChecked);
	}
}

const bool UUtilityActionBase::CheckAllRequirements(UUtilityComponent& OwnerComp) const
{
	if (bUseParallelRequirementChecking)
	{
		return InternalParallelCheckAllRequirements(OwnerComp);
	}
	else
	{
		return InternalCheckAllRequirements(OwnerComp);
	}
}

const bool UUtilityActionBase::CheckAllRequirements(const FMassEntityHandle& Entity) const
{
	if (bUseParallelRequirementChecking)
	{
		return InternalParallelCheckAllRequirements(Entity);
	}
	else
	{
		return InternalCheckAllRequirements(Entity);
	}
}

const bool UUtilityActionBase::InternalCheckAllRequirements(UUtilityComponent& OwnerComp) const
{
	bool bRequirementsPassed = true;
	for (const UUtilityActionRequirementBase* const Requirement : Requirements)
	{
		if (!ensureAlwaysMsgf(IsValid(Requirement), TEXT("Utility Action has an invalid requirement.")))
		{
			continue;
		}

		if (!Requirement->CheckRequirement(OwnerComp))
		{
			bRequirementsPassed = false;
			break;
		}
	}

	return bRequirementsPassed;
}

const bool UUtilityActionBase::InternalCheckAllRequirements(const FMassEntityHandle& Entity) const
{
	bool bRequirementsPassed = true;
	for (const UUtilityActionRequirementBase* const Requirement : Requirements)
	{
		if (!ensureAlwaysMsgf(IsValid(Requirement), TEXT("Utility Action has an invalid requirement.")))
		{
			continue;
		}

		if (!Requirement->CheckRequirement(Entity))
		{
			bRequirementsPassed = false;
			break;
		}
	}

	return bRequirementsPassed;
}

const bool UUtilityActionBase::InternalParallelCheckAllRequirements(UUtilityComponent& OwnerComp) const
{
	FCriticalSection Mutex;
	bool bRequirementsPassed = true;

	ParallelFor(Requirements.Num(), [this, &Mutex, &bRequirementsPassed, &OwnerComp](int32 Index)
		{
			FScopeLock Lock(&Mutex);

			const UUtilityActionRequirementBase* const Requirement = Requirements[Index];
			if (ensureAlwaysMsgf(IsValid(Requirement), TEXT("Utility Action has an invalid requirement.")))
			{
				if (!Requirement->CheckRequirement(OwnerComp))
				{
					bRequirementsPassed = false;
				}
			}
		});

	return bRequirementsPassed;
}

const bool UUtilityActionBase::InternalParallelCheckAllRequirements(const FMassEntityHandle& Entity) const
{
	FCriticalSection Mutex;
	bool bRequirementsPassed = true;

	ParallelFor(Requirements.Num(), [this, &Mutex, &bRequirementsPassed, &Entity](int32 Index)
		{
			FScopeLock Lock(&Mutex);

			const UUtilityActionRequirementBase* const Requirement = Requirements[Index];
			if (ensureAlwaysMsgf(IsValid(Requirement), TEXT("Utility Action has an invalid requirement.")))
			{
				if (!Requirement->CheckRequirement(Entity))
				{
					bRequirementsPassed = false;
				}
			}
		});

	return bRequirementsPassed;
}

void UUtilityActionBase::AsyncCheckAllRequirements(UUtilityComponent& OwnerComp)
{
	if (bUseParallelRequirementChecking)
	{
		InternalParallelAsyncCheckAllRequirements(OwnerComp);
	}
	else
	{
		InternalAsyncCheckAllRequirements(OwnerComp);
	}
}

void UUtilityActionBase::InternalAsyncCheckAllRequirements(UUtilityComponent& OwnerComp)
{
	AsyncRequirementsChecked = 0;
	AsyncRequirementsToBeChecked = 0;
	bAsyncRequirementsPassed = true;

	for (const UUtilityActionRequirementBase* const Requirement : Requirements)
	{
		if (ensureAlwaysMsgf(IsValid(Requirement), TEXT("Utility Action has an invaild requirement.")))
		{
			continue;
		}

		AsyncTask(ENamedThreads::AnyThread, [&Requirement, &OwnerComp]()
			{
				Requirement->AsyncCheckRequirement(OwnerComp);
			});

		AsyncRequirementsToBeChecked++;
	}
}

void UUtilityActionBase::InternalParallelAsyncCheckAllRequirements(UUtilityComponent& OwnerComp)
{
	FCriticalSection Mutex;
	AsyncRequirementsChecked = 0;
	AsyncRequirementsToBeChecked = 0;
	bAsyncRequirementsPassed = true;

	ParallelFor(Requirements.Num(), [this, &Mutex, &OwnerComp](int32 Index)
		{
			FScopeLock Lock(&Mutex);

			const UUtilityActionRequirementBase* const Requirement = Requirements[Index];
			if (ensureAlwaysMsgf(IsValid(Requirement), TEXT("Utility Action has an invalid requirement.")))
			{
				AsyncTask(ENamedThreads::AnyThread, [&Requirement, &OwnerComp]()
					{
						Requirement->AsyncCheckRequirement(OwnerComp);
					});

				AsyncRequirementsToBeChecked++;
			}
		});
}

const float UUtilityActionBase::GetActionScore(UUtilityComponent& OwnerComp) const
{
	float TotalScore = 1.0f;

	const float NumFactors = static_cast<float>(Factors.Num());
	for (const UUtilityActionFactorBase* const Factor : Factors)
	{
		const float FactorScore = Factor->GetFactorScore(OwnerComp, NumFactors);
		TotalScore *= FactorScore != 0.0f ? FactorScore : 1.0f;
	}

	return TotalScore * UtilityWeight;
}

const float UUtilityActionBase::GetActionScore(const FMassEntityHandle& Entity) const
{
	float TotalScore = 1.0f;

	const float NumFactors = static_cast<float>(Factors.Num());
	for (const UUtilityActionFactorBase* const Factor : Factors)
	{
		const float FactorScore = Factor->GetFactorScore(Entity, NumFactors);
		TotalScore *= FactorScore != 0.0f ? FactorScore : 1.0f;
	}

	return TotalScore * UtilityWeight;
}

const EUtilityActionRunStatus& UUtilityActionBase::PerformAction(UUtilityComponent& OwnerComp)
{
	if (CurrentRunStatus == EUtilityActionRunStatus::Running)
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Warning,
			TEXT("%s called on utility action [ %s ] while it is already running."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*GetName()
		);
		return CurrentRunStatus;
	}

	CurrentRunStatus = DoAction(OwnerComp);
	
	if (CurrentRunStatus != EUtilityActionRunStatus::Running)
	{
		// If DoReaction() immeidately completes for any reason, immediately complete here too.
		OnActionCompletedDelegate.Broadcast(this);
		return CurrentRunStatus;
	}

	OwnerComponent = &OwnerComp;
	PrimaryUtilityActionTick.SetTickFunctionEnable(true);

	return CurrentRunStatus;
}

const EUtilityActionRunStatus& UUtilityActionBase::PerformAction(const FMassEntityHandle& Entity)
{
	if (CurrentRunStatus == EUtilityActionRunStatus::Running)
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Warning,
			TEXT("%s called on utility action [ %s ] while it is already running."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*GetName()
		);
		return CurrentRunStatus;
	}

	CurrentRunStatus = DoAction(Entity);

	if (CurrentRunStatus != EUtilityActionRunStatus::Running)
	{
		// If DoReaction() immeidately completes for any reason, immediately complete here too.
		OnActionCompletedDelegate.Broadcast(this);
		return CurrentRunStatus;
	}

	EntityHandle = Entity;
	PrimaryUtilityActionTick.SetTickFunctionEnable(true);

	return CurrentRunStatus;
}

EUtilityActionRunStatus UUtilityActionBase::DoAction(const FMassEntityHandle& Entity)
{
	// Should be overridden, if it is not then this warning triggers
	UE_VLOG_ALWAYS_UELOG(
		this,
		LogUtility,
		Warning,
		TEXT("%s - This Utility Action [ %s ] is not set up for Mass use."),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName()
	);

	return EUtilityActionRunStatus::Succeeded;
}

void UUtilityActionBase::ResetCurrentRunStatus()
{
	CurrentRunStatus = EUtilityActionRunStatus::NotRunning;
}

void UUtilityActionBase::PauseAction(const FString& Reason)
{
	UE_VLOG_ALWAYS_UELOG(
		this,
		LogUtility,
		Log,
		TEXT("%s - Pausing action [ %s ] due to [ %s ]."),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName(),
		*Reason
	);

	PrimaryUtilityActionTick.SetTickFunctionEnable(false);
}

bool UUtilityActionBase::ResumeAction()
{
	UE_VLOG(
		this,
		LogUtility,
		Log,
		TEXT("%s - Resuming action [ %s ]."),
		*GetName()
	);

	PrimaryUtilityActionTick.SetTickFunctionEnable(true);

	return true;
}

void UUtilityActionBase::AbortAction(const FString& Reason)
{
	UE_VLOG_ALWAYS_UELOG(
		this,
		LogUtility,
		Log,
		TEXT("%s - Aborting action [ %s ] due to [ %s ]."),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName(),
		*Reason
	);

	ResetCurrentRunStatus();
	OnActionCompletedDelegate.Broadcast(this);
	PrimaryUtilityActionTick.SetTickFunctionEnable(false);
}

void UUtilityActionBase::TickAction(
	float DeltaTime,
	ELevelTick TickType,
	FUtilityActionTickFunction& ThisTickFunction
)
{
	if (!IsValid(GetWorld()) || (!OwnerComponent.IsValid() && !EntityHandle.IsValid()))
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Log,
			TEXT("%s - Invalid world or owner component/entity handle for Action [ %s ] Aborting."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*GetName()
		);

		AbortAction(FString(TEXT("Invalid World or Owning Component/Entity Handle.")));
		return;
	}

	if (OwnerComponent.IsValid())
	{
		Tick(*OwnerComponent.Get(), DeltaTime);
	}
	else if (EntityHandle.IsValid())
	{
		Tick(EntityHandle, DeltaTime);
	}

	if (CurrentRunStatus != EUtilityActionRunStatus::Running)
	{
		OnActionCompletedDelegate.Broadcast(this);
		PrimaryUtilityActionTick.SetTickFunctionEnable(false);

		const UWorld* const World = GetWorld();
		check(IsValid(World));
		UMassSignalSubsystem* const MassSignalSubsystem = World->GetSubsystem<UMassSignalSubsystem>();
		check(IsValid(MassSignalSubsystem));
		MassSignalSubsystem->SignalEntity(UE::Mass::Signals::NewUtilityActionRequired, EntityHandle);
	}
}

void UUtilityActionBase::Tick(const FMassEntityHandle& Entity, float DeltaSeconds)
{
	// Should be overridden, if it is not then this warning triggers
	UE_VLOG_ALWAYS_UELOG(
		this,
		LogUtility,
		Warning,
		TEXT("%s - This Utility Action [ %s ] is not set up for Mass use."),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName()
	);
}

void UUtilityActionBase::OnAsyncRequirementChecked(const UUtilityActionRequirementBase* const Requirement, const bool bRequirementPassed)
{
	checkf(IsValid(Requirement), TEXT("Delegate received from invalid requirement."));
	
	bAsyncRequirementsPassed = bAsyncRequirementsPassed && bRequirementPassed;
	AsyncRequirementsChecked++;

	if (AsyncRequirementsChecked == AsyncRequirementsToBeChecked)
	{
		OnAsyncRequirementsCheckedDelegate.Broadcast(this, bAsyncRequirementsPassed);
	}
}