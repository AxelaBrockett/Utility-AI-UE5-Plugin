// Fill out your copyright notice in the Description page of Project Settings.

#include "ResearchTeam/RTAICharacter.h"

#include "Components/SceneComponent.h"

ARTAICharacter::ARTAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FollowTransformComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Follow Transform Component"));
}

void ARTAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARTAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}