// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestAIController.generated.h"

class UUtilityComponent;

/**
 * 
 */
UCLASS()
class AIPLUGINPROJECT_API ATestAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATestAIController(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UUtilityComponent> UtilityComponent = nullptr;
};