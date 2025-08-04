// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MassEntityTraitBase.h"

#include "MassUtilityTrait.generated.h"

class UUtilityDataAsset;
class UWorld;
struct FMassEntityTemplateBuildContext;

/**
 * 
 */
UCLASS(meta = (DisplayName = "Utility Data Asset"))
class AIPLUGINPROJECT_API UMassUtilityTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()
	
protected:
	void BuildTemplate(
		FMassEntityTemplateBuildContext& BuildContext,
		const UWorld& World
	) const override;
	bool ValidateTemplate(
		const FMassEntityTemplateBuildContext& BuildContext,
		const UWorld& World,
		FAdditionalTraitRequirements& OutTraitRequirements
	) const override;

	UPROPERTY(EditAnywhere, Category = "Utility Data Asset")
	TObjectPtr<UUtilityDataAsset> UtilityDataAsset = nullptr;
};