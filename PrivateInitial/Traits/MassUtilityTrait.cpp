// Fill out your copyright notice in the Description page of Project Settings.

#include "Traits/MassUtilityTrait.h"

#include "DataAssets/UtilityDataAsset.h"
#include "Engine/World.h"
#include "Helpers/UtilityHelpers.h"
#include "MassAIBehaviorTypes.h"
#include "MassEntityManager.h"
#include "MassEntityTemplateRegistry.h"
#include "MassEntityUtils.h"
#include "VisualLogger/VisualLogger.h"

void UMassUtilityTrait::BuildTemplate(
	FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World
) const
{
	if (!IsValid(UtilityDataAsset))
	{
		UE_VLOG_ALWAYS_UELOG(
			&World,
			LogMassBehavior,
			Error,
			TEXT("%s - Utility Data Asset has not been set."),
			ANSI_TO_TCHAR(__FUNCTION__)
		);
		return;
	}
	
	FMassEntityManager& EntityManager = UE::Mass::Utils::GetEntityManagerChecked(World);

	FMassUtilitySharedFragment SharedUtilityAsset;
	SharedUtilityAsset.UtilityDataAsset = UtilityDataAsset;

	const FConstSharedStruct UtilityAssetFragment = EntityManager.GetOrCreateConstSharedFragment(SharedUtilityAsset);
	BuildContext.AddConstSharedFragment(UtilityAssetFragment);

	BuildContext.AddFragment<FMassUtilityInstanceFragment>();
}

bool UMassUtilityTrait::ValidateTemplate(
	const FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World,
	FAdditionalTraitRequirements& OutTraitRequirements
) const
{
	if (!IsValid(UtilityDataAsset))
	{
		UE_VLOG_ALWAYS_UELOG(
			&World,
			LogMassBehavior,
			Error,
			TEXT("%s - Utility Data Asset has not been set."),
			ANSI_TO_TCHAR(__FUNCTION__)
		);
		return false;
	}

	return true;
}