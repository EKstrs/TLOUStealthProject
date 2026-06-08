// Copyright Epic Games, Inc. All Rights Reserved.

#include "TLOUStealthGameMode.h"
#include "TLOUStealthCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATLOUStealthGameMode::ATLOUStealthGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
