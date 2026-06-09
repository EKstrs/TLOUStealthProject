#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StealthAIController.generated.h"

class UBehaviorTree;


UCLASS()
class AStealthAIController : public AAIController
{
	GENERATED_BODY()


protected:

	virtual void OnPossess(APawn* PossessedPawn) override;


private:

	UPROPERTY(EditdefaultsOnly, Category = "StealthAI")
	UBehaviorTree* BehaviorTree;
	
};
