// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AITypes.h"
#include "BrainComponent.h"
#include "Helpers/UtilityHelpers.h"

#include "UtilityComponent.generated.h"

class UUtilityActionBase;
class UUtilityDataAsset;

enum class EUtilityComponentPauseActionLogic : uint8
{
	PauseAction,
	AbortAction
};

/**
 * Component for running a Utility based decision system
 */
UCLASS(BlueprintType)
class AIPLUGINPROJECT_API UUtilityComponent : public UBrainComponent
{
	GENERATED_BODY()
	
public:
	UUtilityComponent();

	// Begin UBrainComponent overrides
	void SetComponentTickEnabled(bool bEnabled) override;
	void StartLogic() override;
	void PauseLogic(const FString& Reason) override;
	EAILogicResuming::Type ResumeLogic(const FString& Reason) override;
	void RestartLogic() override;
	void StopLogic(const FString& Reason) override;
	// End UBrainComponent overrides

	const UUtilityActionBase* GetCurrentAction() const { return CurrentAction; }
	const UUtilityActionBase* GetLastSuccessfulAction() const { return LastSuccessfulAction; }

	virtual void AbortCurrentAction(const EUtilityAbortActionLogic& AbortLogic);
	virtual void PauseLogicWithActionDecision(const FString& Reason, const EUtilityComponentPauseActionLogic& ActionDecision);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	virtual void OnRep_CurrentAction();

	UFUNCTION()
	virtual void OnRep_LastSuccessfulAction();

	UPROPERTY(ReplicatedUsing = OnRep_CurrentAction)
	TObjectPtr<UUtilityActionBase> CurrentAction = nullptr;

	UPROPERTY(ReplicatedUsing = OnRep_LastSuccessfulAction)
	TObjectPtr<UUtilityActionBase> LastSuccessfulAction = nullptr;

private:
	bool PerformUtilityAction();

	bool RequestUtilityAction();
	void AsyncRequestUtilityAction();

	void GetPossibleActions(TMap<UUtilityActionBase*, const float>& PossibleActionsToScores);
	void ParallelGetPossibleActions(TMap<UUtilityActionBase*, const float>& PossibleActionsToScores);
	void AsyncGetPossibleActions();
	void ParallelAsyncGetPossibleActions();

	void OnActionCompleted(UUtilityActionBase* Action);
	void OnActionRequirementsChecked(UUtilityActionBase* Action, const bool bRequirementsPassed);

	UPROPERTY(EditAnywhere, Category = "Utility")
	TObjectPtr<UUtilityDataAsset> UtilityDataAsset = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UUtilityActionBase>> UtilityActions;

	UPROPERTY(EditAnywhere, Category = "Async")
	bool bUseParallelRequirementChecking = false;

	UPROPERTY(EditAnywhere, Category = "Async")
	bool bRunComponentAsynchronously = false;

	UPROPERTY(EditAnywhere, Category = "Pausing")
	bool bRestartLogicWhenUnPausingComponent = false;

	int32 AsyncActionsToCheck = 0;
	int32 AsyncActionsChecked = 0;
	TMap<UUtilityActionBase*, const float> AsyncPossibleActionsToScores;
};