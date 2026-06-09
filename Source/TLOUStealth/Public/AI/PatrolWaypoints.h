// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolWaypoints.generated.h"

UCLASS()
class APatrolWaypoints : public AActor
{
	GENERATED_BODY()
	
public:	
	APatrolWaypoints();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
	float WaitTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
	bool bLookAround = false;

protected:
	virtual void BeginPlay() override;

	

};
