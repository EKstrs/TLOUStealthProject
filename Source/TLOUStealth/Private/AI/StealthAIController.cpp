// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BlackboardComponent.h"


AStealthAIController::AStealthAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));

	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 2000.f;
	SightConfig->PeripheralVisionAngleDegrees = 80.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	HearingConfig->HearingRange = 2000.f;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->ConfigureSense(*HearingConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AStealthAIController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	if (BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);
	}
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AStealthAIController::OnTargetDetected);
}

void AStealthAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (!Actor || !Actor->ActorHasTag(TEXT("Player"))) return;
	
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		bIsSeeingPlayer = Stimulus.WasSuccessfullySensed();

		if (!GetWorldTimerManager().IsTimerActive(DetectionTimerHandle))
		{
			GetWorldTimerManager().SetTimer(DetectionTimerHandle, this, &AStealthAIController::UpdateDetectionMeter, 0.1f, true);
		}
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		
	}
}

void AStealthAIController::UpdateDetectionMeter()
{
	if (bIsSeeingPlayer)
	{
		CurrentDetectionLevel = FMath::Clamp<float>(CurrentDetectionLevel + 0.05f, 0.0f, 1.0f);
	}
	else
	{
		CurrentDetectionLevel = FMath::Clamp<float>(CurrentDetectionLevel - 0.025f, 0.0f, 1.0f);
	}
	if (UBlackboardComponent* BBComp = GetBlackboardComponent())
	{
		BBComp->SetValueAsFloat(TEXT("DetectionLevel"), CurrentDetectionLevel);
	}
	
	if (!bIsSeeingPlayer && CurrentDetectionLevel <= 0.0f)
	{
		GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
	}
}
