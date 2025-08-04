// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actions/ActionFactors/UtilityActionFactorBase.h"

#include "UtilityActionFactorDistToTarget.generated.h"

class UUtilityComponent;

/**
 * 
 */
UCLASS(meta = (DisplayName = "Distance To Closest Hostile Actor"))
class AIPLUGINPROJECT_API UUtilityActionFactorDistToTarget : public UUtilityActionFactorBase
{
	GENERATED_BODY()
	
protected:
	const float CalculateFactorScore(UUtilityComponent& OwnerComp) const override;

private:
	UPROPERTY(EditAnywhere, Category = "Distance")
	float MaxDistance = 1000.0f;
};