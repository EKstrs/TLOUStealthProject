// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetNextWaypoint.h"
#include "AI/AICharacter.h"
#include "AI/PatrolWaypoints.h"
#include "AI/StealthAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTask_GetNextWaypoint::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* AIController = owner_comp.GetAIOwner();

	if (AAICharacter* AICharacter = Cast<AAICharacter>(AIController->GetPawn()))
	{
		int CurrentIndex = AICharacter->WayPointIndex;
		APatrolWaypoints* CurrentWaypoint = AICharacter->WayPoints[CurrentIndex];

		if (!CurrentWaypoint) return  EBTNodeResult::Failed;

		FVector Location = CurrentWaypoint->GetActorLocation();
		float TimeToWait = CurrentWaypoint->WaitTime;

		UBlackboardComponent* AIBlackboard = owner_comp.GetBlackboardComponent();
		AIBlackboard->SetValueAsVector(TargetLocation.SelectedKeyName, Location);
		AIBlackboard->SetValueAsFloat(WaitTime.SelectedKeyName, TimeToWait);

		AICharacter->WayPointIndex++;

		if (AICharacter->WayPointIndex >= AICharacter->WayPoints.Num())
		{
			AICharacter->WayPointIndex = 0;
		}
		return EBTNodeResult::Succeeded;
	}
	
	else
	{
		return EBTNodeResult::Failed;
	}
}
