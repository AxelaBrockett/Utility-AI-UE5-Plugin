// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RTAIController.generated.h"

class UBehaviorTreeComponent;

/**
 * AI Controller for the research team
 */
UCLASS()
class AIPLUGINPROJECT_API ARTAIController : public AAIController
{
	GENERATED_BODY()

public:
	ARTAIController(const FObjectInitializer& ObjectInitializer);
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BTComp;
};