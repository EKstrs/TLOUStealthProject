// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_GetNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()


public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetLocation;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector WaitTime; 
};
