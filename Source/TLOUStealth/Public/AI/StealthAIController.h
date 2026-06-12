#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StealthAIController.generated.h"

struct FAIStimulus;
class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

UCLASS()
class AStealthAIController : public AAIController
{
	GENERATED_BODY()

public: 

    AStealthAIController();
    
protected:

	virtual void OnPossess(APawn* PossessedPawn) override;

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Perception")
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
        
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Perception")
    TObjectPtr<UAISenseConfig_Sight> SightConfig;
        
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Perception")
    TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

    /*Detection meter*/
    FTimerHandle DetectionTimerHandle;
    float CurrentDetectionLevel = 0.0f;
    bool bIsSeeingPlayer = false;
    void UpdateDetectionMeter();

private:

	UPROPERTY(EditdefaultsOnly, Category = "StealthAI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

   	
};
