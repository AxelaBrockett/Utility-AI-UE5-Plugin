// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/UtilityComponent.h"

#include "Actions/UtilityActionBase.h"
#include "DataAssets/UtilityDataAsset.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "VisualLogger/VisualLogger.h"

UUtilityComponent::UUtilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bTickEvenWhenPaused = false;
}

void UUtilityComponent::SetComponentTickEnabled(bool bEnabled)
{
	UE_VLOG_ALWAYS_UELOG(
		GetOwner(),
		LogUtility,
		Warning,
		TEXT("%s - Utility Component does not have a tick. Forcing tick to false."),
		ANSI_TO_TCHAR(__FUNCTION__)
	);

	Super::SetComponentTickEnabled(false);
}

void UUtilityComponent::StartLogic()
{
	checkf(IsValid(UtilityDataAsset), TEXT("Utility Component should always have a valid Utility Data Asset."));

	// Bind to action delegates
	for (UUtilityActionBase* const Action : UtilityDataAsset->GetActions())
	{
		if (!ensureAlwaysMsgf(IsValid(Action), TEXT("Utility Data Asset has invalid action.")))
		{
			continue;
		}

		UtilityActions.Add(Action);
		Action->OnActionCompletedDelegate.AddDynamic(this, &UUtilityComponent::OnActionCompleted);
		Action->OnAsyncRequirementsCheckedDelegate.AddDynamic(this, &UUtilityComponent::OnActionRequirementsChecked);
		Action->BindToRequirementDelegates();
	}

	if (!PerformUtilityAction())
	{
		StopLogic(FString(TEXT("Could not start logic.")));
	}
}

void UUtilityComponent::PauseLogicWithActionDecision(const FString& Reason, const EUtilityComponentPauseActionLogic& ActionDecision)
{
	switch (ActionDecision)
	{
		case (EUtilityComponentPauseActionLogic::PauseAction):
		{
			CurrentAction->PauseAction(FString(TEXT("Pausing component logic with Action Decision to pause action.")));
			break;
		}
		case (EUtilityComponentPauseActionLogic::AbortAction):
		default:
		{
			if (IsValid(CurrentAction))
			{
				CurrentAction->AbortAction(FString(TEXT("Pausing component logic with Action Decision to abort action.")));
				CurrentAction = nullptr;
			}
			break;
		}
	}

	PauseLogic(Reason);
}

void UUtilityComponent::PauseLogic(const FString& Reason)
{
	UE_VLOG_ALWAYS_UELOG(
		GetOwner(),
		LogUtility,
		Log,
		TEXT("%s - Pausing logic for utility component [ %s ] due to: %s"),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName(),
		*Reason
	);

	Super::PauseLogic(Reason);
}

EAILogicResuming::Type UUtilityComponent::ResumeLogic(const FString& Reason)
{
	if (bRestartLogicWhenUnPausingComponent)
	{
		RestartLogic();
		return EAILogicResuming::RestartedInstead;
	}
	
	if (IsValid(CurrentAction))
	{
		if (!CurrentAction->ResumeAction())
		{
			UE_VLOG_ALWAYS_UELOG(
				GetOwner(),
				LogUtility,
				Warning,
				TEXT("%s - Failed to resume action [ %s ]. Attempting to choose new action."),
				ANSI_TO_TCHAR(__FUNCTION__),
				*CurrentAction->GetName()
			);

			AbortCurrentAction(EUtilityAbortActionLogic::ChooseNewAction);
		}
	}
	else
	{
		if (!PerformUtilityAction())
		{
			StopLogic(FString(TEXT("Could not find new action.")));
		}
	}

	return EAILogicResuming::Continue;
}

void UUtilityComponent::RestartLogic()
{
	StopLogic(FString(TEXT("Restarting logic.")));
	StartLogic();
}

void UUtilityComponent::StopLogic(const FString& Reason)
{
	UE_VLOG_ALWAYS_UELOG(
		GetOwner(),
		LogUtility,
		Log,
		TEXT("%s - Stopping logic for utility component [ %s ] due to: %s"),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName(),
		*Reason
	);

	if (IsValid(CurrentAction))
	{
		CurrentAction->AbortAction(FString(TEXT("Stopping component logic.")));
		CurrentAction = nullptr;
	}

	for (UUtilityActionBase* const Action : UtilityActions)
	{
		if (!IsValid(Action))
		{
			continue;
		}

		Action->OnActionCompletedDelegate.RemoveDynamic(this, &UUtilityComponent::OnActionCompleted);
	}

	UtilityActions.Reset();

	Super::StopLogic(Reason);
}

void UUtilityComponent::AbortCurrentAction(const EUtilityAbortActionLogic& AbortLogic)
{
	switch (AbortLogic)
	{
		case (EUtilityAbortActionLogic::StopComponent):
		{
			StopLogic(FString(TEXT("Aborting action with [ EUtilityAbortActionLogic::StopComponent ].")));
			break;
		}
		case (EUtilityAbortActionLogic::PauseLogicPauseAction):
		{
			PauseLogicWithActionDecision(FString(TEXT("Pausing component logic and current action.")), EUtilityComponentPauseActionLogic::PauseAction);
			break;
		}
		case (EUtilityAbortActionLogic::PauseLogicAbortAction):
		{
			PauseLogicWithActionDecision(FString(TEXT("Aborting current action with choice to pause logic.")), EUtilityComponentPauseActionLogic::AbortAction);
			break;
		}
		case (EUtilityAbortActionLogic::ChooseNewAction):
		{
			if (IsValid(CurrentAction))
			{
				CurrentAction->AbortAction(FString(TEXT("Aborting to choose new action.")));
				CurrentAction = nullptr;
			}

			if (!PerformUtilityAction())
			{
				StopLogic(FString(TEXT("Could not find new action.")));
			}
			break;
		}
		default:
		{
			UE_VLOG_ALWAYS_UELOG(
				GetOwner(),
				LogUtility,
				Error,
				TEXT("%s - No valid abort logic passed in."),
				ANSI_TO_TCHAR(__FUNCTION__)
			);
			break;
		}
	}
}

bool UUtilityComponent::PerformUtilityAction()
{
	if (bRunComponentAsynchronously)
	{
		AsyncRequestUtilityAction();
		return true;
	}

	if (!RequestUtilityAction())
	{
		UE_VLOG_ALWAYS_UELOG(
			GetOwner(),
			LogUtility,
			Error,
			TEXT("%s - Utility Component [ %s ] could not perform a valid action."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*GetName()
		);
		return false;
	}

	return true;
}

bool UUtilityComponent::RequestUtilityAction()
{
	if (UtilityActions.IsEmpty())
	{
		// No actions to pick from, failing here.
		return false;
	}

	TMap<UUtilityActionBase*, const float> PossibleActionsToScores;

	if (bUseParallelRequirementChecking)
	{
		ParallelGetPossibleActions(PossibleActionsToScores);
	}
	else
	{
		GetPossibleActions(PossibleActionsToScores);
	}
	
	if (PossibleActionsToScores.IsEmpty())
	{
		// No possible actions as all requirements failed, failing here.
		return false;
	}

	PossibleActionsToScores.ValueStableSort([](const float& First, const float& Second) -> bool
		{
			return First > Second;
		}
	);

	EUtilityActionRunStatus ActionStatus = EUtilityActionRunStatus::Failed;
	for (TPair<UUtilityActionBase*, const float>& ActionPair : PossibleActionsToScores)
	{
		ActionStatus = ActionPair.Key->PerformAction(*this);

		if (ActionStatus != EUtilityActionRunStatus::Failed)
		{
			CurrentAction = ActionPair.Key;
			break;
		}
	}

	return ActionStatus != EUtilityActionRunStatus::Failed;
}

void UUtilityComponent::AsyncRequestUtilityAction()
{
	if (UtilityActions.IsEmpty())
	{
		UE_VLOG_ALWAYS_UELOG(
			GetOwner(),
			LogUtility,
			Warning,
			TEXT("%s - Utility Component [ %s ] has no actions."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*GetName()
		);
		StopLogic(FString(TEXT("Could not find new action.")));
		return;
	}

	if (bUseParallelRequirementChecking)
	{
		ParallelAsyncGetPossibleActions();
	}
	else
	{
		AsyncGetPossibleActions();
	}
}

void UUtilityComponent::GetPossibleActions(TMap<UUtilityActionBase*, const float>& PossibleActionsToScores)
{
	for (UUtilityActionBase* const Action : UtilityActions)
	{
		if (!ensureAlwaysMsgf(IsValid(Action), TEXT("Utility Data Asset has invalid action.")))
		{
			continue;
		}
		const float ActionScore = Action->GetActionScore(*this);
		if (Action->CheckAllRequirements(*this) && ActionScore > 0.0f)
		{
			PossibleActionsToScores.Add(Action, ActionScore);
		}
	}
}

void UUtilityComponent::ParallelGetPossibleActions(TMap<UUtilityActionBase*, const float>& PossibleActionsToScores)
{
	FCriticalSection Mutex;

	// Parallel get actions that pass their requirements
	ParallelFor(UtilityActions.Num(), [this, &Mutex, &PossibleActionsToScores](int32 Index)
		{
			FScopeLock Lock(&Mutex);

			UUtilityActionBase* const Action = UtilityActions[Index];
			if (ensureAlwaysMsgf(IsValid(Action), TEXT("Utility Data Asset has invalid action.")))
			{
				const float ActionScore = Action->GetActionScore(*this);
				if (Action->CheckAllRequirements(*this) && ActionScore > 0.0f)
				{
					PossibleActionsToScores.Add(Action, ActionScore);
				}
			}
		});
}

void UUtilityComponent::AsyncGetPossibleActions()
{
	AsyncActionsChecked = 0;
	AsyncActionsToCheck = 0;
	AsyncPossibleActionsToScores.Empty();

	for (UUtilityActionBase* const Action : UtilityActions)
	{
		if (!ensureAlwaysMsgf(IsValid(Action), TEXT("Utility Component has an invalid action.")))
		{
			continue;
		}

		AsyncTask(ENamedThreads::AnyThread, [this, &Action]()
			{
				Action->AsyncCheckAllRequirements(*this);
			});

		AsyncActionsToCheck++;
	}
}

void UUtilityComponent::ParallelAsyncGetPossibleActions()
{
	FCriticalSection Mutex;

	AsyncActionsChecked = 0;
	AsyncActionsToCheck = 0;
	AsyncPossibleActionsToScores.Empty();

	ParallelFor(UtilityActions.Num(), [this, &Mutex](int32 Index)
		{
			FScopeLock Lock(&Mutex);

			UUtilityActionBase* const Action = UtilityActions[Index];
			if (ensureAlwaysMsgf(IsValid(Action), TEXT("Utility Component has an invalid action.")))
			{
				AsyncTask(ENamedThreads::AnyThread, [this, &Action]()
					{
						Action->AsyncCheckAllRequirements(*this);
					});

				AsyncActionsToCheck++;
			}
		});
}

void UUtilityComponent::OnActionCompleted(UUtilityActionBase* Action)
{
	checkf(IsValid(Action), TEXT("Delegate received from invalid action."));

	switch (Action->GetCurrentRunStatus())
	{
		case(EUtilityActionRunStatus::Running):
		{
			checkf(false, TEXT("Utility Component has received an Action Completed notification while the action [ %s ] is still running."), *Action->GetName());
			break;
		}
		case(EUtilityActionRunStatus::Succeeded):
		{
			LastSuccessfulAction = Action;
			break;
		}
		case(EUtilityActionRunStatus::Failed):
		{
			UE_VLOG_ALWAYS_UELOG(
				GetOwner(),
				LogUtility,
				Warning,
				TEXT("%s - Action [ %s ] has failed."),
				ANSI_TO_TCHAR(__FUNCTION__),
				*Action->GetName()
			);
			break;
		}
		case(EUtilityActionRunStatus::NotRunning):
		default:
		{
			break;
		}
	}

	Action->ResetCurrentRunStatus();
	CurrentAction = nullptr;

	const UWorld* const World = GetWorld();
	if (!IsValid(World))
	{
		UE_VLOG_ALWAYS_UELOG(
			GetOwner(),
			LogUtility,
			Error,
			TEXT("%s - Could not find a valid world."),
			ANSI_TO_TCHAR(__FUNCTION__)
		);
		StopLogic(FString(TEXT("Could not find a valid world.")));
	}

	FTimerManager& TimerManager = World->GetTimerManager();
	TimerManager.SetTimerForNextTick([this]()
		{
			if (!PerformUtilityAction())
			{
				StopLogic(FString(TEXT("Could not find new action.")));
			}
		}
	);
}

void UUtilityComponent::OnActionRequirementsChecked(UUtilityActionBase* Action, const bool bRequirementsPassed)
{
	checkf(IsValid(Action), TEXT("Delegate Received from invalid action."));

	AsyncActionsChecked++;

	if (bRequirementsPassed)
	{
		const float ActionScore = Action->GetActionScore(*this);
		if (ActionScore > 0.0f)
		{
			AsyncPossibleActionsToScores.Add(Action, ActionScore);
		}
	}

	if (AsyncActionsChecked != AsyncActionsToCheck)
	{
		return;
	}

	if (AsyncPossibleActionsToScores.IsEmpty())
	{
		UE_VLOG_ALWAYS_UELOG(
			GetOwner(),
			LogUtility,
			Warning,
			TEXT("%s - Utility Component [ %s ] could not find a new action. Aborting."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*GetName()
		);
		StopLogic(FString(TEXT("Could not find appropriate action. Aborting.")));
		return;
	}

	AsyncPossibleActionsToScores.ValueStableSort([](const float& First, const float& Second) -> bool
		{
			return First > Second;
		}
	);

	EUtilityActionRunStatus ActionStatus = EUtilityActionRunStatus::Failed;
	for (TPair<UUtilityActionBase*, const float>& ActionPair : AsyncPossibleActionsToScores)
	{
		ActionStatus = ActionPair.Key->PerformAction(*this);

		if (ActionStatus != EUtilityActionRunStatus::Failed)
		{
			CurrentAction = ActionPair.Key;
			break;
		}
	}
}

void UUtilityComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UUtilityComponent, CurrentAction);
	DOREPLIFETIME(UUtilityComponent, LastSuccessfulAction);
}

void UUtilityComponent::OnRep_CurrentAction()
{

}

void UUtilityComponent::OnRep_LastSuccessfulAction()
{

}