// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"


class APatrolWaypoints;
class UWidgetComponent;


UCLASS()
class AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AAICharacter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = AI)
	int WayPointIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	TArray<APatrolWaypoints*> WayPoints;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> PatrolStatusWidget;
	

};
