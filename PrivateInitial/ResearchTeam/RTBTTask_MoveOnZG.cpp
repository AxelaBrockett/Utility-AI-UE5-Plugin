// Fill out your copyright notice in the Description page of Project Settings.

#include "ResearchTeam/RTBTTask_MoveOnZG.h"

#include "AIController.h"
#include "AITypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/Pawn.h"
#include "Navigation/PathFollowingComponent.h"
#include "ResearchTeam/RTAICharacter.h"
#include "ZoneGraphSubsystem.h"

URTBTTask_MoveOnZG::URTBTTask_MoveOnZG(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Move On Zone Graph";
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

uint16 URTBTTask_MoveOnZG::GetInstanceMemorySize() const
{
	return sizeof(FRTBTTask_MoveOnZGMemory);
}

EBTNodeResult::Type URTBTTask_MoveOnZG::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UWorld* const World = GetWorld();
	check(IsValid(World));
	const UZoneGraphSubsystem* const ZoneGraphSubsystem = World->GetSubsystem<UZoneGraphSubsystem>();
	check(IsValid(ZoneGraphSubsystem));

	FRTBTTask_MoveOnZGMemory* Memory = CastInstanceNodeMemory<FRTBTTask_MoveOnZGMemory>(NodeMemory);

	AAIController* const Controller = OwnerComp.GetAIOwner();
	check(IsValid(Controller));
	APawn* const AIPawn = Controller->GetPawn();
	check(IsValid(AIPawn));

	if (!StartNewPath(*Controller, *AIPawn, *Memory, *ZoneGraphSubsystem))
	{
		UE_VLOG(
			Controller,
			LogBehaviorTree,
			Error,
			TEXT("%s - Failed to start a new path for pawn [ %s ]. Failing task."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*AIPawn->GetName()
		);
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void URTBTTask_MoveOnZG::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const UWorld* const World = GetWorld();
	check(IsValid(World));
	const UZoneGraphSubsystem* const ZoneGraphSubsystem = World->GetSubsystem<UZoneGraphSubsystem>();
	check(IsValid(ZoneGraphSubsystem));

	FRTBTTask_MoveOnZGMemory* Memory = CastInstanceNodeMemory<FRTBTTask_MoveOnZGMemory>(NodeMemory);

	AAIController* const Controller = OwnerComp.GetAIOwner();
	check(IsValid(Controller));
	APawn* const AIPawn = Controller->GetPawn();
	check(IsValid(AIPawn));

	if (!FollowPath(*Controller, *AIPawn, *Memory, *ZoneGraphSubsystem))
	{
		UE_VLOG(
			Controller,
			LogBehaviorTree,
			Error,
			TEXT("%s - Pawn [ %s ] failed to follow zone graph [ %s ]. Failing task."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*AIPawn->GetName(),
			*Memory->CurrentLane.LaneHandle.ToString()
		);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
}

bool URTBTTask_MoveOnZG::StartNewPath(AAIController& Controller, APawn& Pawn, FRTBTTask_MoveOnZGMemory& Memory, const UZoneGraphSubsystem& ZoneGraphSubsystem)
{
	FZoneGraphLaneLocation NearestLane;

	const FVector PawnLocation = Pawn.GetActorLocation();
	const FVector LaneQueryVector(ZoneGraphQueryRadius);
	const FBox QueryBounds(PawnLocation - LaneQueryVector, PawnLocation + LaneQueryVector);
	float NearestLaneDistSqr = 0.0f;

	const ARTAICharacter* const RTCharacter = Cast<ARTAICharacter>(&Pawn);
	check(IsValid(RTCharacter));

	FZoneGraphTagFilter TagFilter;
	TagFilter.AnyTags = RTCharacter->GetZoneGraphTags();

	const bool bFoundZGLane = ZoneGraphSubsystem.FindNearestLane(QueryBounds, TagFilter, NearestLane, NearestLaneDistSqr);

	if (!bFoundZGLane)
	{
		UE_VLOG(
			&Controller,
			LogBehaviorTree,
			Error,
			TEXT("%s - ZoneGraphSubsystem [ %s ] failed to find a nearest lane to character [ %s ]."),
			ANSI_TO_TCHAR(__FUNCTION__),
			*ZoneGraphSubsystem.GetName(),
			*RTCharacter->GetName()
		);
		return false;
	}

	Memory.CurrentLane = NearestLane;

	return true;
}

bool URTBTTask_MoveOnZG::FollowPath(AAIController& Controller, APawn& AIPawn, FRTBTTask_MoveOnZGMemory& Memory, const UZoneGraphSubsystem& ZoneGraphSubsystem)
{
	// Check if we're within radius of the point
	// If no, move towards the point, return
	// If yes, check if we're at the end of the lane
	// If no, advance the lane location, maybe move as well
	// If yes, go to the next lane

	if (!Memory.CurrentLane.IsValid())
	{
		UE_VLOG(
			&Controller,
			LogBehaviorTree,
			Error,
			TEXT("%s - Current lane is invalid."),
			ANSI_TO_TCHAR(__FUNCTION__)
		);
		return false;
	}

	const float DistanceToLanePositionSquared = FVector::DistSquared(AIPawn.GetActorLocation(), Memory.CurrentLane.Position);
	const float AcceptanceRadiusSquared = PointFollowingAcceptanceRadius * PointFollowingAcceptanceRadius;

	// If we're not close enough to the point yet, continue moving towards it
	if (DistanceToLanePositionSquared > AcceptanceRadiusSquared)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetNavigationFilter(Controller.GetDefaultNavigationFilterClass());
		MoveRequest.SetAllowPartialPath(true);
		MoveRequest.SetAcceptanceRadius(NavigationSettings.PointFollowingAcceptanceRadius);
		MoveRequest.SetCanStrafe(false);
		MoveRequest.SetReachTestIncludesAgentRadius(true);
		MoveRequest.SetReachTestIncludesGoalRadius(true);
		MoveRequest.SetRequireNavigableEndLocation(false);
		MoveRequest.SetProjectGoalLocation(false);
		MoveRequest.SetUsePathfinding(false);
		MoveRequest.SetStartFromPreviousPath(true);
		MoveRequest.SetGoalLocation(Memory.CurrentLane.Position);

		if (!MoveRequest.IsValid())
		{
			UE_VLOG(
				&Controller,
				LogBehaviorTree,
				Error,
				TEXT("%s - Failed to generate a valid Move Request."),
				ANSI_TO_TCHAR(__FUNCTION__)
			);
			return false;
		}

		const FPathFollowingRequestResult& Result = Controller.MoveTo(MoveRequest);

		switch (Result.Code)
		{
			case(EPathFollowingRequestResult::RequestSuccessful):
			case(EPathFollowingRequestResult::AlreadyAtGoal):
				return true;
				break;
			case(EPathFollowingRequestResult::Failed):
			default:
				UE_VLOG(
					&Controller,
					LogBehaviorTree,
					Error,
					TEXT("%s - Controller [ %s ] failed to move pawn [ %s ] towards goal point [ X: %f | Y: %f | Z: %f ]."),
					ANSI_TO_TCHAR(__FUNCTION__),
					*Controller.GetName(),
					*AIPawn.GetName(),
					Memory.CurrentLane.Position.X,
					Memory.CurrentLane.Position.Y,
					Memory.CurrentLane.Position.Z
				);
				return false;
				break;
		}
	}

	// If we're close enough to the point...
	if ((DistanceToLanePositionSquared < AcceptanceRadiusSquared))
	{
		float DistAlongLane = 0.0f;
		// ... and the point is at the end of the lane, move to the next lane...
		if (FMath::IsNearlyZero(ZoneGraphSubsystem.GetLaneLength(Memory.CurrentLane.LaneHandle, DistAlongLane) - Memory.CurrentLane.DistanceAlongLane))
		{
			FZoneGraphLinkedLane NextLane;
			if (!ZoneGraphSubsystem.GetFirstLinkedLane(Memory.CurrentLane.LaneHandle, EZoneLaneLinkType::Outgoing, EZoneLaneLinkFlags::All, EZoneLaneLinkFlags::None, NextLane))
			{
				UE_VLOG(
					&Controller,
					LogBehaviorTree,
					Error,
					TEXT("%s - Zone Graph Subsystem [ %s ] failed to find a next zone graph point for pawn [ %s ]."),
					ANSI_TO_TCHAR(__FUNCTION__),
					*ZoneGraphSubsystem.GetName(),
					*AIPawn.GetName()
				);
				return false;
			}

			if (!NextLane.IsValid())
			{
				UE_VLOG(
					&Controller,
					LogBehaviorTree,
					Error,
					TEXT("%s - Zone Graph Subsystem [ %s ] returned an invalid linked lane."),
					ANSI_TO_TCHAR(__FUNCTION__),
					*ZoneGraphSubsystem.GetName()
				);
				return false;
			}

			FZoneGraphLaneLocation StartOfNextLane;
			if (!ZoneGraphSubsystem.CalculateLocationAlongLane(NextLane.DestLane, 0.0f, StartOfNextLane))
			{
				UE_VLOG(
					&Controller,
					LogBehaviorTree,
					Error,
					TEXT("%s - Zone Graph Subsystem [ %s ] could not calculate the start of the lane [ %s ]."),
					ANSI_TO_TCHAR(__FUNCTION__),
					*ZoneGraphSubsystem.GetName(),
					*NextLane.DestLane.ToString()
				);
				return false;
			}

			if (!StartOfNextLane.IsValid())
			{
				UE_VLOG(
					&Controller,
					LogBehaviorTree,
					Error,
					TEXT("%s - Zone Graph Subsystem [ %s ] returned an invalid lane location."),
					ANSI_TO_TCHAR(__FUNCTION__),
					*ZoneGraphSubsystem.GetName()
				);
				return false;
			}

			Memory.CurrentLane = StartOfNextLane;
			return true;
		}

		// ...otherwise advance the lane location
		FZoneGraphLaneLocation AdvancedLaneLocation;
		ZoneGraphSubsystem.AdvanceLaneLocation(Memory.CurrentLane, 500.0f, AdvancedLaneLocation);
		if (!AdvancedLaneLocation.IsValid())
		{
			UE_VLOG(
				&Controller,
				LogBehaviorTree,
				Error,
				TEXT("%s - Zone Graph Subsystem [ %s ] returned an invalid advanced lane location."),
				ANSI_TO_TCHAR(__FUNCTION__),
				*ZoneGraphSubsystem.GetName()
			);
			return false;
		}

		return true;
	}

	// If we reach here, nothing has happened, which is bad
	return false;
}