// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCppGameMode.h"
#include "UnrealCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealCppGameMode::AUnrealCppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
