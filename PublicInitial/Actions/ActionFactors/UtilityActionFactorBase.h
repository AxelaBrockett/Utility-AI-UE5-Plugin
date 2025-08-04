// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MassEntityTypes.h"
#include "UObject/NoExportTypes.h"

#include "UtilityActionFactorBase.generated.h"

class UUtilityComponent;

/**
 * Base for factors that will affect the score of a Utility Action.
 */
UCLASS(EditInlineNew, Abstract)
class AIPLUGINPROJECT_API UUtilityActionFactorBase : public UObject
{
	GENERATED_BODY()
	
public:
	// Decides the score for the factor affecting the Utility Action, between 0 and 1.
	const float GetFactorScore(UUtilityComponent& OwnerComp, const float NumberOfFactors) const;
	const float GetFactorScore(const FMassEntityHandle& Entity, const float NumberOfFactors) const;

	const bool IsInversed() const;

protected:
	virtual const float CalculateFactorScore(UUtilityComponent& OwnerComp) const { return 1.0f; }
	virtual const float CalculateFactorScore(const FMassEntityHandle& Entity) const;

private:
	void AddConsiderationFactor(const float NumberOfFactors, float& OutFloat) const;

	UPROPERTY(EditAnywhere, Category = "Scoring")
	uint32 bInverseScore : 1;
};

FORCEINLINE const bool UUtilityActionFactorBase::IsInversed() const
{
	return bInverseScore;
}