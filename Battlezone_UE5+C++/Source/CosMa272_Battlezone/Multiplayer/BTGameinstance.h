// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BTGameinstance.generated.h"

/**
 * 
 */
UCLASS()
class COSMA272_BATTLEZONE_API UBTGameinstance : public UGameInstance
{
	GENERATED_BODY()

private:
	const char* ipAddress = "192.168.1.40";
	TSubclassOf<UUserWidget> MainMenu;

public:
	void Init();
	UBTGameinstance();

	UFUNCTION(Exec)
		void Join();

	UFUNCTION(Exec)
		void Host();
};
