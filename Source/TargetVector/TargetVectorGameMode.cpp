// Copyright Epic Games, Inc. All Rights Reserved.

#include "TargetVectorGameMode.h"
#include "TargetVectorCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATargetVectorGameMode::ATargetVectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/B_ThirdPerson_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
