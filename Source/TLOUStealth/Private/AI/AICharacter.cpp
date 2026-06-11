// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/StealthAIController.h"
#include "Components/WidgetComponent.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//Use custom AI brain (this is default backup if BP is not set in editor)
	AIControllerClass = AStealthAIController::StaticClass();
	//Make sure the AI is possessed whether placed or spawned
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    //Debug widget for AI status
	PatrolStatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PatrolStatusWidget"));
	PatrolStatusWidget->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PatrolStatusWidget->SetWidgetSpace(EWidgetSpace::World);
	PatrolStatusWidget->SetVisibility(true);
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}
