// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actions/UtilityActionBase.h"
#include "Helpers/UtilityHelpers.h"
#include "MassEntityTypes.h"

#include "UtilityActionBlueprintBase.generated.h"

class UUtilityComponent;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class AIPLUGINPROJECT_API UUtilityActionBlueprintBase : public UUtilityActionBase
{
	GENERATED_BODY()

public:
	void Tick(UUtilityComponent& OwnerComp, float DeltaSeconds) override;
	void Tick(const FMassEntityHandle& Entity, float DeltaSeconds) override;
	
protected:
	EUtilityActionRunStatus DoAction(UUtilityComponent& OwnerComp) override;
	EUtilityActionRunStatus DoAction(const FMassEntityHandle& Entity) override;

	UFUNCTION(BlueprintNativeEvent)
	void DoBlueprintAction(UUtilityComponent* OwnerComp);

	UFUNCTION(BlueprintNativeEvent)
	void DoMassBlueprintAction(const FMassEntityHandleBlueprintWrapper Entity);

	UFUNCTION(BlueprintNativeEvent)
	void TickBlueprintAction(UUtilityComponent* OwnerComp, float DeltaSeconds);

	UFUNCTION(BlueprintNativeEvent)
	void TickMassBlueprintAction(const FMassEntityHandleBlueprintWrapper Entity, float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	void FinishAction(bool bSuccess);
};