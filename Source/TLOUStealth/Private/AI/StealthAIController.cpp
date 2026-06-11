// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
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

	if (BehaviorTree !=  nullptr)
	{
		RunBehaviorTree(BehaviorTree);
	}
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AStealthAIController::OnTargetDetected);
}

void AStealthAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (GetBlackboardComponent())
		{
			GetBlackboardComponent()->SetValueAsBool(TEXT("IsAlerted"), true);
		}
	}
	else
	{
		if (GetBlackboardComponent())
		{
			GetBlackboardComponent()->SetValueAsBool(TEXT("IsAlerted"), false);
		}
	}
}
