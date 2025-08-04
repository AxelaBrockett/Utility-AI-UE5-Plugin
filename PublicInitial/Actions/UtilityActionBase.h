// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/EngineBaseTypes.h"
#include "Helpers/UtilityHelpers.h"
#include "MassEntityTypes.h"
#include "UObject/NoExportTypes.h"

#include "UtilityActionBase.generated.h"

class UUtilityActionFactorBase;
class UUtilityActionRequirementBase;
class UUtilityComponent;

USTRUCT()
struct FUtilityActionTickFunction : public FTickFunction
{
	GENERATED_BODY()

	// Action that is the target of this tick
	class UUtilityActionBase* Action;

	// Abstract function actually execute the tick.
	void ExecuteTick(
		float DeltaTime,
		ELevelTick TickType,
		ENamedThreads::Type CurrentThread,
		const FGraphEventRef& MyCompletionGraphEvent
	) override;


	FString DiagnosticMessage() override;
	FName DiagnosticContext(bool bDetailed) override;
};

template<>
struct TStructOpsTypeTraits<FUtilityActionTickFunction> : public TStructOpsTypeTraitsBase2<FUtilityActionTickFunction>
{
	enum
	{
		WithCopy = false
	};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionCompletedDelegate, UUtilityActionBase*, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAsyncRequirementsChecked, UUtilityActionBase*, Action, const bool, bRequirementsPassed);

/**
 * Base for Utility Actions.
 */
UCLASS(EditInlineNew)
class AIPLUGINPROJECT_API UUtilityActionBase : public UObject
{
	GENERATED_BODY()

public:
	UUtilityActionBase();

	void BindToRequirementDelegates() const;

	const bool CheckAllRequirements(UUtilityComponent& OwnerComp) const;
	const bool CheckAllRequirements(const FMassEntityHandle& Entity) const;
	void AsyncCheckAllRequirements(UUtilityComponent& OwnerComp);

	const float GetActionScore(UUtilityComponent& OwnerComp) const;
	const float GetActionScore(const FMassEntityHandle& Entity) const;

	const EUtilityActionRunStatus& PerformAction(UUtilityComponent& OwnerComp);
	const EUtilityActionRunStatus& PerformAction(const FMassEntityHandle& Entity);

	const EUtilityActionRunStatus& GetCurrentRunStatus() const { return CurrentRunStatus; }
	void ResetCurrentRunStatus();

	virtual void PauseAction(const FString& Reason);
	virtual bool ResumeAction();
	virtual void AbortAction(const FString& Reason);
	
	virtual void TickAction(
		float DeltaTime,
		enum ELevelTick TickType,
		FUtilityActionTickFunction& ThisTickFunction
	);
	virtual void Tick(UUtilityComponent& OwnerComp, float DeltaSeconds) {}
	virtual void Tick(const FMassEntityHandle& Entity, float DeltaSeconds);

	// If true, actor is ticked even if TickType == LEVELTICK_ViewportsOnly
	virtual bool ShouldTickIfViewportsOnly() const { return false; }

	FOnActionCompletedDelegate OnActionCompletedDelegate;
	FOnAsyncRequirementsChecked OnAsyncRequirementsCheckedDelegate;

	UPROPERTY(EditDefaultsOnly, Category = Tick)
	struct FUtilityActionTickFunction PrimaryUtilityActionTick;

protected:
	virtual EUtilityActionRunStatus DoAction(UUtilityComponent& OwnerComp) { return EUtilityActionRunStatus::Succeeded; }
	virtual EUtilityActionRunStatus DoAction(const FMassEntityHandle& Entity);

	EUtilityActionRunStatus CurrentRunStatus = EUtilityActionRunStatus::NotRunning;
	TWeakObjectPtr<UUtilityComponent> OwnerComponent;
	FMassEntityHandle EntityHandle;
	
private:
	const bool InternalCheckAllRequirements(UUtilityComponent& OwnerComp) const;
	const bool InternalCheckAllRequirements(const FMassEntityHandle& Entity) const;
	const bool InternalParallelCheckAllRequirements(UUtilityComponent& OwnerComp) const;
	const bool InternalParallelCheckAllRequirements(const FMassEntityHandle& Entity) const;
	void InternalAsyncCheckAllRequirements(UUtilityComponent& OwnerComp);
	void InternalParallelAsyncCheckAllRequirements(UUtilityComponent& OwnerComp);

	void OnAsyncRequirementChecked(const UUtilityActionRequirementBase* const Requirement, const bool bRequirementPassed);

	// Weight multiplier for Utility Scoring. Gets multiplied at the end of the scoring.
	UPROPERTY(EditAnywhere, meta = (ClampMin="0.0", ClampMax="1.0"))
	float UtilityWeight = 0.0f;

	UPROPERTY(EditAnywhere)
	bool bUseParallelRequirementChecking = false;

	// The list of requirements for the action to be possible
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UUtilityActionRequirementBase>> Requirements;

	// The list of factors affecting the utility score of the action
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UUtilityActionFactorBase>> Factors;

	int32 AsyncRequirementsToBeChecked = 0;
	int32 AsyncRequirementsChecked = 0;
	bool bAsyncRequirementsPassed = true;
};