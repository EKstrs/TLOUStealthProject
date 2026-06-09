// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StealthAIController.h"




void AStealthAIController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	if (BehaviorTree !=  nullptr)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
