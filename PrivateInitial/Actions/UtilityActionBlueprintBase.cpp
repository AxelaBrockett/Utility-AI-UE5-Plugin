// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/UtilityActionBlueprintBase.h"

#include "Components/UtilityComponent.h"

EUtilityActionRunStatus UUtilityActionBlueprintBase::DoAction(UUtilityComponent& OwnerComp)
{
	CurrentRunStatus = EUtilityActionRunStatus::Running;
	DoBlueprintAction(&OwnerComp);
	return CurrentRunStatus;
}

EUtilityActionRunStatus UUtilityActionBlueprintBase::DoAction(const FMassEntityHandle& Entity)
{
	CurrentRunStatus = EUtilityActionRunStatus::Running;
	FMassEntityHandleBlueprintWrapper EntityBlueprintWrapper;
	EntityBlueprintWrapper.EntityHandle = Entity;
	DoMassBlueprintAction(EntityBlueprintWrapper);
	return CurrentRunStatus;
}

void UUtilityActionBlueprintBase::DoBlueprintAction_Implementation(UUtilityComponent* OwnerComp)
{
	
}

void UUtilityActionBlueprintBase::DoMassBlueprintAction_Implementation(const FMassEntityHandleBlueprintWrapper Entity)
{

}

void UUtilityActionBlueprintBase::Tick(UUtilityComponent& OwnerComp, float DeltaSeconds)
{
	TickBlueprintAction(&OwnerComp, DeltaSeconds);
}

void UUtilityActionBlueprintBase::Tick(const FMassEntityHandle& Entity, float DeltaSeconds)
{
	FMassEntityHandleBlueprintWrapper EntityBlueprintWrapper;
	EntityBlueprintWrapper.EntityHandle = Entity;
	TickMassBlueprintAction(EntityBlueprintWrapper, DeltaSeconds);
}

void UUtilityActionBlueprintBase::TickBlueprintAction_Implementation(UUtilityComponent* OwnerComp, float DeltaSeconds)
{

}

void UUtilityActionBlueprintBase::TickMassBlueprintAction_Implementation(const FMassEntityHandleBlueprintWrapper Entity, float DeltaSeconds)
{

}

void UUtilityActionBlueprintBase::FinishAction(bool bSuccess)
{
	CurrentRunStatus = bSuccess ? EUtilityActionRunStatus::Succeeded : EUtilityActionRunStatus::Failed;
}