// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionFactors/UtilityActionFactorDistToTarget.h"

#include "AIController.h"
#include "Components/UtilityComponent.h"
#include "GameFramework/Pawn.h"
#include "Helpers/UtilityHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "VisualLogger/VisualLogger.h"

const float UUtilityActionFactorDistToTarget::CalculateFactorScore(UUtilityComponent& OwnerComp) const
{
	const AAIController* const AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController))
	{
		UE_VLOG_ALWAYS_UELOG(
			&OwnerComp,
			LogUtility,
			Warning,
			TEXT("%s - Utility Component [ %s ] does not have a valid AI Controller Owner."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*OwnerComp.GetName()
		);
		return 0.0f;
	}

	const APawn* const AIPawn = AIController->GetPawn();
	if (!IsValid(AIPawn))
	{
		UE_VLOG_ALWAYS_UELOG(
			&OwnerComp,
			LogUtility,
			Warning,
			TEXT("%s - AI Controller [ %s ] does not have a valid Pawn."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*AIController->GetName()
		);
		return 0.0f;
	}

	const UAIPerceptionComponent* const PerceptionComponent = AIController->GetAIPerceptionComponent();
	if (!IsValid(PerceptionComponent))
	{
		UE_VLOG_ALWAYS_UELOG(
			&OwnerComp,
			LogUtility,
			Warning,
			TEXT("%s - AI Controller [ %s ] does not have a valid Perception Component."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*AIController->GetName()
		);
		return 0.0f;
	}

	const float MaxDistanceSqr = MaxDistance * MaxDistance;

	TArray<AActor*> HostileActors;
	PerceptionComponent->GetHostileActors(HostileActors);

	float LowestDistance = FLT_MAX;
	for (const AActor* const HostileActor : HostileActors)
	{
		const float DistanceToActor = FVector::DistSquared(AIPawn->GetActorLocation(), HostileActor->GetActorLocation());
		LowestDistance = DistanceToActor < LowestDistance ? DistanceToActor : LowestDistance;
	}

	if (LowestDistance > MaxDistanceSqr)
	{
		return 0.0f;
	}

	return (MaxDistanceSqr - LowestDistance) / MaxDistanceSqr;
}