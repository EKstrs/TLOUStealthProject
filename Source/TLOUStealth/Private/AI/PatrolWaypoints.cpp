// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PatrolWaypoints.h"

#include "AI/AICharacter.h"
#include "Components/BillboardComponent.h"

APatrolWaypoints::APatrolWaypoints()
{

	PrimaryActorTick.bCanEverTick = false;
	UBillboardComponent* VisualPoint =  CreateDefaultSubobject<UBillboardComponent>(TEXT("VisualPoint"));
	SetRootComponent(VisualPoint);
}

void APatrolWaypoints::BeginPlay()
{
	Super::BeginPlay();
	
}

void APatrolWaypoints::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

