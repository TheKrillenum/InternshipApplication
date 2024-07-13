// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h"
#include "Engine/GameInstance.h"
#include "BZGameInstance.generated.h"

/**
 *
 */
UCLASS()
class COSMA272_BATTLEZONE_API UBZGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	// Private variable
	TSubclassOf<UUserWidget> MainMenuClass;
	TSubclassOf<UUserWidget> PauseMenuClass;
	const FName MySessionName = FName("COOL SESSION"); 
	const FName ServerNameKey = FName("ServerName");
	IOnlineSessionPtr MySessionInterface;
	FOnlineSessionSettings MySessionSettings;
	TSharedPtr<FOnlineSessionSearch> SessionSearchCriteria;
	FString serverCustomName = ("Default server name");
	IOnlineSubsystem* Subsystem = nullptr;
	int numberOfPlayers = 0;
	const FName SearchKey = FName("SEARCH_PRESENCE");
	// For some reason SEACH_PRESENCE is not recognized, but since it's an FName i just set to to another variable that I set.

	// Private function
	void CreateGameSession(FString CustomServerName);
	void OnCreateSession(FName SessionName, bool success);
	void OnDestroySession(FName SessionName, bool success);
	void OnFindSession(bool success);
	void OnJoinSession(FName JoinedSessionName, EOnJoinSessionCompleteResult::Type Result);

	// Listeners
	TArray<class UBZMainMenu*> Listeners;
	void NotifyListeners(TArray<struct FServerData> ArrayOfServer);
	void RegisterListener(UBZMainMenu* inMainMenu);

public:

	// Public function
		void Init();
		UBZGameInstance();
		int GetNumberOfPlayers();
		void SetNumberOfPlayers();
		void ReturnMainMenu();

		UFUNCTION(Exec)
		void JoinLAN(const FString& ipAddress);
		UFUNCTION(Exec)
		void HostLAN();

		void SoloGame();
		void JoinOnline(int32 index);
		void HostOnline(FString CustomServerName);

		void SearchAvailableSessions();

	UFUNCTION(BlueprintCallable)
		void LoadMainMenu();

	UFUNCTION(BlueprintCallable, Exec)
		void StartLevel();

	UFUNCTION(BlueprintCallable)
		UBZPauseMenu* LoadPauseMenu();

	UFUNCTION(BlueprintCallable)
		void MenuInputMode();

	UFUNCTION(BlueprintCallable)
		void GameplayInputMode();
};