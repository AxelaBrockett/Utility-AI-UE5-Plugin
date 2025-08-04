// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ZoneGraphTypes.h"

#include "RTBTTask_MoveOnZG.generated.h"

class AAIController;
class APawn;
class UBehaviorTreeComponent;
class UNavigationQueryFilter;
class UZoneGraphSubsystem;
struct FZoneGraphTagFilter;

USTRUCT()
struct FRTBTTask_MoveToNavigationSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Navigation")
	float PointFollowingAcceptanceRadius = 500.0f;
};

struct FRTBTTask_MoveOnZGMemory
{
	FZoneGraphLaneLocation CurrentLane;

	bool bNeedsNewPath = false;
};

/**
 * 
 */
UCLASS()
class AIPLUGINPROJECT_API URTBTTask_MoveOnZG : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	URTBTTask_MoveOnZG(const FObjectInitializer& ObjectInitializer);

	uint16 GetInstanceMemorySize() const override;
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool StartNewPath(AAIController& Controller, APawn& AIPawn, FRTBTTask_MoveOnZGMemory& Memory, const UZoneGraphSubsystem& ZoneGraphSubsystem);
	bool FollowPath(AAIController& Controller, APawn& AIPawn, FRTBTTask_MoveOnZGMemory& Memory, const UZoneGraphSubsystem& ZoneGraphSubsystem);

	UPROPERTY(EditAnywhere, Category = "Zone Graph|Find Zone Graph")
	float ZoneGraphQueryRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Navigation")
	float PointFollowingAcceptanceRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Navigation")
	FRTBTTask_MoveToNavigationSettings NavigationSettings;
};