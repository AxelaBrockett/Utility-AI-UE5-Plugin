// Fill out your copyright notice in the Description page of Project Settings.

#include "ResearchTeam/RTAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

ARTAIController::ARTAIController(const FObjectInitializer& ObjectInitializer)
{
	bStartAILogicOnPossess = true;
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComp"));
	BrainComponent = BTComp;
}