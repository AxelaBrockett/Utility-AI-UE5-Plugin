// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actions/ActionRequirements/UtilityActionRequirementBase.h"
#include "MassEntityTypes.h"

#include "UtilityActionRequirementHasActor.generated.h"

class UUtilityComponent;

/**
 * 
 */
UCLASS(meta = (DisplayName = "Has Actor"))
class AIPLUGINPROJECT_API UUtilityActionRequirementHasActor : public UUtilityActionRequirementBase
{
	GENERATED_BODY()
	
public:
	const bool CheckRequirement(UUtilityComponent& OwnerComp) const override;
	const bool CheckRequirement(const FMassEntityHandle& Entity) const override;
};