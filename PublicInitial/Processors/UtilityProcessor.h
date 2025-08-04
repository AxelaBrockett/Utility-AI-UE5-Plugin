// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MassProcessor.h"
#include "MassSignalProcessorBase.h"

#include "UtilityProcessor.generated.h"

struct FMassEntityManager;
struct FMassEntityQuery;
struct FMassExecutionContext;
struct FMassSignalNameLookup;

UCLASS()
class AIPLUGINPROJECT_API UUtilityActivationProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UUtilityActivationProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void ConfigureQueries() override;
	void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};

/**
 * 
 */
UCLASS()
class AIPLUGINPROJECT_API UUtilityProcessor : public UMassSignalProcessorBase
{
	GENERATED_BODY()
	
public:
	UUtilityProcessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void Initialize(UObject& Owner) override;
	void ConfigureQueries() override;
	void SignalEntities(FMassEntityManager& EntityManager, FMassExecutionContext& Context, FMassSignalNameLookup& EntitySignals) override;
};