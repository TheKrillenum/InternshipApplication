// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class COSMA272_BATTLEZONE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
private:

public:
	virtual void NativeConstruct() override;
};
