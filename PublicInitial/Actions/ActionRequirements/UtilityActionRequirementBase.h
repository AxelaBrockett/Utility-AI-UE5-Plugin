// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MassEntityTypes.h"
#include "UObject/NoExportTypes.h"

#include "UtilityActionRequirementBase.generated.h"

class UUtilityComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAsyncRequirementChecked, const UUtilityActionRequirementBase*, Requirement, const bool, bRequirementPassed);

/**
 * Base for the requirements of a utility action
 */
UCLASS(EditInlineNew, Abstract)
class AIPLUGINPROJECT_API UUtilityActionRequirementBase : public UObject
{
	GENERATED_BODY()
	
public:
	// Check the requirement. True means the requirement is met, false means it is not.
	virtual const bool CheckRequirement(UUtilityComponent& OwnerComp) const { return true; };
	virtual const bool CheckRequirement(const FMassEntityHandle& Entity) const;

	// Version of CheckRequirement called asynchronously that broadcasts when checked
	void AsyncCheckRequirement(UUtilityComponent& OwnerComp) const;

	FOnAsyncRequirementChecked OnAsyncRequirementCheckedDelegate;
};