// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DataAssets/UtilityDataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MassEntityTypes.h"

#include "UtilityHelpers.generated.h"

class UUtilityActionBase;

DECLARE_LOG_CATEGORY_EXTERN(LogUtility, Display, All);

UENUM(BlueprintType)
enum class EUtilityActionRunStatus : uint8
{
	NotRunning,
	Running,
	Succeeded,
	Failed
};

UENUM()
enum class EUtilityAbortActionLogic : uint8
{
	StopComponent,
	PauseLogicPauseAction,
	PauseLogicAbortAction,
	ChooseNewAction
};

namespace UE::Mass::Signals
{
	const FName NewUtilityActionRequired = FName(TEXT("NewUtilityActionRequired"));
}

USTRUCT()
struct AIPLUGINPROJECT_API FMassUtilityActivatedTag : public FMassTag
{
	GENERATED_BODY()
};

USTRUCT()
struct AIPLUGINPROJECT_API FMassUtilitySharedFragment : public FMassConstSharedFragment
{
	GENERATED_BODY()

	FMassUtilitySharedFragment() = default;

	TObjectPtr<UUtilityDataAsset> UtilityDataAsset = nullptr;
};

USTRUCT()
struct AIPLUGINPROJECT_API FMassUtilityInstanceFragment : public FMassFragment
{
	GENERATED_BODY()

	FMassUtilityInstanceFragment() = default;

	TObjectPtr<UUtilityActionBase> CurrentAction;
	TObjectPtr<UUtilityActionBase> LastSuccessfulAction;
	TArray<TObjectPtr<UUtilityActionBase>> UtilityActions;
};

USTRUCT(BlueprintType)
struct AIPLUGINPROJECT_API FMassEntityHandleBlueprintWrapper
{
	GENERATED_BODY()

	FMassEntityHandleBlueprintWrapper() = default;

	static FMassEntityHandleBlueprintWrapper FromNumber(uint64 Value)
	{
		FMassEntityHandleBlueprintWrapper Result;
		Result.EntityHandle = FMassEntityHandle::FromNumber(Value);
		return Result;
	}

	FMassEntityHandle EntityHandle;
};

/**
 * 
 */
UCLASS()
class AIPLUGINPROJECT_API UUtilityBlueprintHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Mass|Entity")
	static bool IsBlueprintEntityWrapperSet(FMassEntityHandleBlueprintWrapper EntityWrapper)
	{
		return EntityWrapper.EntityHandle.IsSet();
	}

	UFUNCTION(BlueprintCallable, Category = "Mass|Entity")
	static bool IsBlueprintEntityWrapperValid(FMassEntityHandleBlueprintWrapper EntityWrapper)
	{
		return EntityWrapper.EntityHandle.IsValid();
	}

	UFUNCTION(BlueprintCallable, Category = "Mass|Entity")
	static void ResetBlueprintEntityWrapper(FMassEntityHandleBlueprintWrapper EntityWrapper)
	{
		EntityWrapper.EntityHandle.Reset();
	}

	UFUNCTION(BlueprintCallable, Category = "Mass|Entity")
	static int64 BlueprintEntityWrapperAsNumber(FMassEntityHandleBlueprintWrapper EntityWrapper)
	{
		return EntityWrapper.EntityHandle.AsNumber();
	}

	UFUNCTION(BlueprintCallable, Category = "Mass|Entity")
	static FMassEntityHandleBlueprintWrapper BlueprintEntityWrapperFromNumber(int64 Value)
	{
		return FMassEntityHandleBlueprintWrapper::FromNumber(Value);
	}

	UFUNCTION(BlueprintCallable, Category = "Mass|Entity")
	static int32 GetBlueprintEntityWrapperTypeHash(FMassEntityHandleBlueprintWrapper EntityWrapper)
	{
		return HashCombine(EntityWrapper.EntityHandle.Index, EntityWrapper.EntityHandle.SerialNumber);
	}

	UFUNCTION(BlueprintCallable, Category = "Mass|Entity")
	static FString DebugGetBlueprintEntityWrapperDescription(FMassEntityHandleBlueprintWrapper EntityWrapper)
	{
		return EntityWrapper.EntityHandle.DebugGetDescription();
	}
};