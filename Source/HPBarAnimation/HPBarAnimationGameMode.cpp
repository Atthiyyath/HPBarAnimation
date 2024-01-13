// Copyright Epic Games, Inc. All Rights Reserved.

#include "HPBarAnimationGameMode.h"
#include "HPBarAnimationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHPBarAnimationGameMode::AHPBarAnimationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
