// Fill out your copyright notice in the Description page of Project Settings.


#include "BZPauseMenu.h"

void UBZPauseMenu::QuitGameButton()
{
	gameInstance->ReturnMainMenu();
}

void UBZPauseMenu::SetGameInstance(UBZGameInstance* setter)
{
	gameInstance = setter;
}

void UBZPauseMenu::NativeDestruct()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) { return; };

	FInputModeGameOnly InputMode;
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = false;
	Super::NativeDestruct();
}