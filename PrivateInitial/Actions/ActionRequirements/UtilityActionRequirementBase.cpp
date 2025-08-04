// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionRequirements/UtilityActionRequirementBase.h"

#include "Components/UtilityComponent.h"
#include "Helpers/UtilityHelpers.h"
#include "VisualLogger/VisualLogger.h"

const bool UUtilityActionRequirementBase::CheckRequirement(const FMassEntityHandle& Entity) const
{
	UE_VLOG_ALWAYS_UELOG(
		this,
		LogUtility,
		Warning,
		TEXT("%s - Utility Action Requirement [ %s ] has not been set up for Mass use."),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName()
	);

	return true;
}

void UUtilityActionRequirementBase::AsyncCheckRequirement(UUtilityComponent& OwnerComp) const
{
	const bool bRequirementHasPassed = CheckRequirement(OwnerComp);
	OnAsyncRequirementCheckedDelegate.Broadcast(this, bRequirementHasPassed);
}