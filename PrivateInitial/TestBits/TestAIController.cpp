// Fill out your copyright notice in the Description page of Project Settings.

#include "TestBits/TestAIController.h"

#include "Components/UtilityComponent.h"

ATestAIController::ATestAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bStartAILogicOnPossess = true;

	UtilityComponent = CreateDefaultSubobject<UUtilityComponent>(TEXT("UtilityComponent"));
	BrainComponent = UtilityComponent;
}