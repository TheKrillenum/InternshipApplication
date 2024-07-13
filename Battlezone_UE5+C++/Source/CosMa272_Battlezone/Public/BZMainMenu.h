// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/Button.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/WidgetSwitcher.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/EditableText.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/ScrollBox.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/BackgroundBlur.h"
#include "BZGameInstance.h"
#include "BZServerDisplayRow.h"
#include "BZMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class COSMA272_BATTLEZONE_API UBZMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Variables
	TArray<UBZServerDisplayRow*> arrayOfServers;

	// Functions
	void SetGameInstance(UBZGameInstance* setter);
	UBZMainMenu(const FObjectInitializer& ObjectInitializer);
	void PopulateServerDisplayRow(TArray<struct FServerData> ServerNames);
	void SetSelectedIndex(int32 index);
	void DeselectAllServer();

private:

	// Variables -----
	UBZGameInstance* gameInstance = nullptr;
	TSubclassOf<UBZServerDisplayRow> ServerDisplayRowClass;
	int32 SelectedIndex = 0;

	// Functions -----
	bool Initialize();
	void NativeDestruct();
	void SetServerVisibility(bool bVisibility);

	// main menu function --------------------------------------------------------------------------------------
	UFUNCTION()
	void SoloGameButtonPressed();

	UFUNCTION()
	void LanMultiplayerButtonPressed();

	UFUNCTION()
	void OnlineMultiplayerButtonPressed();

	UFUNCTION()
	void CreditButtonPressed();

	UFUNCTION()
	void QuitButtonPressed();

	// lan function

	UFUNCTION()
	void HostLanButtonPressed();

	UFUNCTION()
	void JoinLanButtonPressed();

	UFUNCTION()
	void QuitLanButtonPressed();

	// online function

	UFUNCTION()
	void HostOnlineButtonPressed();

	UFUNCTION()
	void JoinOnlineButtonPressed();

	UFUNCTION()
	void QuitOnlineButtonPressed();

	UFUNCTION()
	void JoinServerButtonPressed();

	UFUNCTION()
	void QuitJoinButtonPressed();

	// credits function

	UFUNCTION()
	void QuitCreditButtonPressed();

	// BINDINGS ----------------------------------------------------------------------------------------

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> OnlineSwitcher;

	// MAIN MENU BINDINGS

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SoloGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LanMultiplayerButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OnlineMultiplayerButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreditButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	// LAN MULTIPLAYER BINDINGS
	// 0_Multiplayer Choice
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HostLanButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinLanButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> LanEditableText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitLanButton;

	// 1_MultiplayerJoin

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinServer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitJoin;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBackgroundBlur> ServerVisibility;

	// ONLINE MULTIPLAYER BINDINGS

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HostOnlineButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> OnlineEditableText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> JoinOnlineButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitOnlineButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ServerDisplayBox;

	// CREDITS BINDINGS

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitCreditButton;
};

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString ServerName, PlayerName;
	int32 CurrentPlayerNumber, MaxPlayerNumber;
};