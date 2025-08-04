// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actions/ActionRequirements/UtilityActionRequirementBase.h"
#include "AITypes.h"
#include "MassEntityTypes.h"
#include "Templates/SubclassOf.h"

#include "UtilityActionRequirementSenseVal.generated.h"

class AAIController;
class UAISense;
class UUtilityComponent;
struct FAIStimulus;

/**
 * 
 */
UCLASS(meta = (DisplayName = "Highest Sense Value Comparison"))
class AIPLUGINPROJECT_API UUtilityActionRequirementSenseVal : public UUtilityActionRequirementBase
{
	GENERATED_BODY()
	
public:
	const bool CheckRequirement(UUtilityComponent& OwnerComp) const override;
	const bool CheckRequirement(const FMassEntityHandle& Entity) const override;

private:
	const bool IsSenseValueAboveMinimum(const AAIController& AIController) const;
	const float GetHighestStrengthFromStimuli(const TArray<FAIStimulus>& Stimuli) const;

	// If not set, all senses will be checked
	UPROPERTY(EditAnywhere, Category = "Sense")
	TSubclassOf<UAISense> SenseToUse;

	// The goal sense value between 0.0 and 1.0
	UPROPERTY(EditAnywhere, Category = "Sense", meta = (ClampMin = 0.0, ClampMax = 1.0))
	float GoalSenseValue = 0.0f;

	// The type of comparison
	UPROPERTY(EditAnywhere, Category = "Sense")
	EGenericAICheck ValueComparison = EGenericAICheck::Equal;
};