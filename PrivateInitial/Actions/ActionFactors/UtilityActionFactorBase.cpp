// Fill out your copyright notice in the Description page of Project Settings.

#include "Actions/ActionFactors/UtilityActionFactorBase.h"

#include "Components/UtilityComponent.h"
#include "Helpers/UtilityHelpers.h"
#include "VisualLogger/VisualLogger.h"

const float UUtilityActionFactorBase::GetFactorScore(UUtilityComponent& OwnerComp, const float NumberOfFactors) const
{
	const float BaseScore = IsInversed() ? 1.0f - CalculateFactorScore(OwnerComp) : CalculateFactorScore(OwnerComp);

	float FinalScore = BaseScore;
	AddConsiderationFactor(NumberOfFactors, FinalScore);

	return FinalScore;
}

const float UUtilityActionFactorBase::GetFactorScore(const FMassEntityHandle& Entity, const float NumberOfFactors) const
{
	const float BaseScore = IsInversed() ? 1.0f - CalculateFactorScore(Entity) : CalculateFactorScore(Entity);

	float FinalScore = BaseScore;
	AddConsiderationFactor(NumberOfFactors, FinalScore);

	return FinalScore;
}

void UUtilityActionFactorBase::AddConsiderationFactor(const float NumberOfFactors, float& OutFloat) const
{
	// Implement Consideration Factor described in this video:
	// https://gdcvault.com/play/1021848/Building-a-Better-Centaur-AI
	const float ModificationFactor = 1.0f - (1.0f / NumberOfFactors);
	const float MakeUpValue = (1.0f - OutFloat) * ModificationFactor;
	const float FinalScore = OutFloat + (MakeUpValue * OutFloat);
}

const float UUtilityActionFactorBase::CalculateFactorScore(const FMassEntityHandle& Entity) const
{
	// Should be overridden, if it is not then this warning triggers
	UE_VLOG_ALWAYS_UELOG(
		this,
		LogUtility,
		Warning,
		TEXT("%s - This Utility Action Factor [ %s ] is not set up for Mass use."),
		ANSI_TO_TCHAR(__FUNCTION__),
		*GetName()
	);

	return 1.0f;
}