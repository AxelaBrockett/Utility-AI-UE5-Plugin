// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZoneGraphTypes.h"
#include "RTAICharacter.generated.h"

class USceneComponent;

UCLASS()
class AIPLUGINPROJECT_API ARTAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARTAICharacter();

	void Tick(float DeltaTime) override;

	const USceneComponent* GetFollowTransformComponent() const { return FollowTransformComponent; }
	const FZoneGraphTagMask& GetZoneGraphTags() const { return TagMask; }

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Research Team")
	TObjectPtr<USceneComponent> FollowTransformComponent;

	// The tags used by the BT for navigation within the transition levels
	UPROPERTY(EditInstanceOnly, Category = "Research Team")
	FZoneGraphTagMask TagMask;
};