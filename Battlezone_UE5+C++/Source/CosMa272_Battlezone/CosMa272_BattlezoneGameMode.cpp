// Copyright Epic Games, Inc. All Rights Reserved.

#include "CosMa272_BattlezoneGameMode.h"
#include "CosMa272_BattlezoneCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACosMa272_BattlezoneGameMode::ACosMa272_BattlezoneGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
