// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetNextWaypoint.h"
#include "AI/AICharacter.h"
#include "AI/PatrolWaypoints.h"
#include "AI/StealthAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTask_GetNextWaypoint::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* AIController = owner_comp.GetAIOwner();

	if(!AIController) return EBTNodeResult::Failed;
	
	if (AAICharacter* AICharacter = Cast<AAICharacter>(AIController->GetPawn()))
	{
		int CurrentIndex = AICharacter->WayPointIndex;
		if (AICharacter->WayPoints.IsEmpty() || !AICharacter->WayPoints.IsValidIndex(CurrentIndex))
		{
			UE_LOG(LogTemp, Warning, TEXT("Waypoints is empty or Current index is not valid"));
			return EBTNodeResult::Failed;
		}
		APatrolWaypoints* CurrentWaypoint = AICharacter->WayPoints[CurrentIndex];

		if (!CurrentWaypoint) return  EBTNodeResult::Failed;

		FVector Location = CurrentWaypoint->GetActorLocation();
		float TimeToWait = CurrentWaypoint->WaitTime;

		UBlackboardComponent* AIBlackboard = owner_comp.GetBlackboardComponent();
		if(!AIBlackboard) return EBTNodeResult::Failed;
		AIBlackboard->SetValueAsVector(TargetLocation.SelectedKeyName, Location);
		AIBlackboard->SetValueAsFloat(WaitTime.SelectedKeyName, TimeToWait);

		AICharacter->WayPointIndex++;

		if (AICharacter->WayPointIndex >= AICharacter->WayPoints.Num())
		{
			AICharacter->WayPointIndex = 0;
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
