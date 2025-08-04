// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionRequirements/UtilityActionRequirementHasActor.h"

#include "AIController.h"
#include "Components/UtilityComponent.h"
#include "Engine/World.h"
#include "Helpers/UtilityHelpers.h"
#include "MassActorSubsystem.h"
#include "VisualLogger/VisualLogger.h"

const bool UUtilityActionRequirementHasActor::CheckRequirement(UUtilityComponent& OwnerComp) const
{
	const AAIController* const AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController))
	{
		UE_VLOG_ALWAYS_UELOG(
			OwnerComp.GetOwner(),
			LogUtility,
			Warning,
			TEXT("%s - Utility Component [ %s ] does not have a valid AI Owner."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*OwnerComp.GetName()
		);
		return false;
	}

	return IsValid(AIController->GetPawn());
}

const bool UUtilityActionRequirementHasActor::CheckRequirement(const FMassEntityHandle& Entity) const
{
	const UWorld* const World = GetWorld();
	if (!IsValid(World))
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Error,
			TEXT("%s - Invalid world."),
			ANSI_TO_TCHAR(__FUNCTION__)
		);
		return false;
	}

	const UMassActorSubsystem* const MassActorSubsystem = World->GetSubsystem<UMassActorSubsystem>();
	if (!IsValid(MassActorSubsystem))
	{
		UE_VLOG_ALWAYS_UELOG(
			this,
			LogUtility,
			Warning,
			TEXT("%s - World [ %s ] has no valid Mass Actor Subsystem."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*World->GetName()
		);
		return false;
	}

	return IsValid(MassActorSubsystem->GetActorFromHandle(Entity));
}