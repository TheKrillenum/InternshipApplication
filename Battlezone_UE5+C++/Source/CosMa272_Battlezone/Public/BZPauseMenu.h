// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/BackgroundBlur.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/Button.h"
#include "BZGameInstance.h"
#include "BZPauseMenu.generated.h"


/**
 * 
 */
UCLASS()
class COSMA272_BATTLEZONE_API UBZPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
private:
	// PRIVATE VARIABLES
	UBZGameInstance* gameInstance;

	UFUNCTION()
	void QuitGameButton();

public:
	//PUBLIC FUNCTIONS
	void SetGameInstance(UBZGameInstance* setter);
	void NativeDestruct();
};
