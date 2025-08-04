// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "UtilityDataAsset.generated.h"

class UUtilityActionBase;

/**
 * 
 */
UCLASS()
class AIPLUGINPROJECT_API UUtilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	const TArray<TObjectPtr<UUtilityActionBase>> GetActions() const { return Actions; }
	
private:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UUtilityActionBase>> Actions;
};