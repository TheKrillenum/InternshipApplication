// Fill out your copyright notice in the Description page of Project Settings.


#include "BZGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "BZMainMenu.h"
#include "BZPauseMenu.h"

UBZGameInstance::UBZGameInstance()
{
	// Finding and saving the Main Menu class
	ConstructorHelpers::FClassFinder<UUserWidget> WBPMainMenu(TEXT("/Game/Battlezone/UI/WBP_MainMenu"));
	if (!ensure(WBPMainMenu.Class != nullptr)) { return; }
	MainMenuClass = WBPMainMenu.Class;
	UE_LOG(LogTemp, Warning, TEXT("Widget created: %s"), *MainMenuClass->GetName());

	// Finding and saving the Main Menu class
	ConstructorHelpers::FClassFinder<UUserWidget> WBPPausePenu(TEXT("/Game/Battlezone/UI/PauseMenu/WBP_Pause"));
	if (!ensure(WBPPausePenu.Class != nullptr)) { return; }
	PauseMenuClass = WBPPausePenu.Class;
	UE_LOG(LogTemp, Warning, TEXT("Widget created: %s"), *PauseMenuClass->GetName());

	Subsystem = nullptr;
}

void UBZGameInstance::CreateGameSession(FString CustomServerName)
{

	if (MySessionInterface->GetNamedSession(MySessionName) == nullptr) {

		if ((Subsystem->GetSubsystemName().ToString()) == "NULL"){

			MySessionSettings.bIsLANMatch = true;
		}
		else {
			MySessionSettings.bIsLANMatch = false;
		}

		// Set the session's setting before creating it
		MySessionSettings.bUsesPresence = true;
		MySessionSettings.bUseLobbiesIfAvailable = true;	// Test if false perhaps ?
		MySessionSettings.NumPublicConnections = 4;
		MySessionSettings.bShouldAdvertise = true;
		MySessionSettings.Set(ServerNameKey, CustomServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		MySessionInterface->CreateSession(0, MySessionName, MySessionSettings);
	}
	else {
		serverCustomName = CustomServerName;
		MySessionInterface->DestroySession(MySessionName);
	}
}

void UBZGameInstance::OnCreateSession(FName SessionName, bool success)
{
	if (success && SessionName == MySessionName) {
		// Travel with the server
		UE_LOG(LogTemp, Warning, TEXT("Session creation succesfull, traveling"));
		UWorld* world = GetWorld();
		if (!ensure(world != nullptr)) { return; }
		world->ServerTravel("/Game/Battlezone/Levels/Lobby?listen");
	}
	else if (!success) {
		UE_LOG(LogTemp, Warning, TEXT("Session creation failed"));
	}
}

void UBZGameInstance::OnDestroySession(FName SessionName, bool success)
{
	if (success) {
		CreateGameSession(serverCustomName);
		serverCustomName = ("Default server name");
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Session destruction failed"));
		serverCustomName = ("Default server name");
	}
}

void UBZGameInstance::OnFindSession(bool success)
{
	if (success) {
		UE_LOG(LogTemp, Warning, TEXT("Found a session"));
		TArray<struct FServerData> ArrayOfServer = TArray<FServerData>();

		for (const FOnlineSessionSearchResult& SearchResult : SessionSearchCriteria->SearchResults) {
			UE_LOG(LogTemp, Warning, TEXT("Session %s found."), *SearchResult.GetSessionIdStr());
			FServerData ServerData;
			FString Name;
			if (SearchResult.Session.SessionSettings.Get(ServerNameKey, Name)) {
				ServerData.ServerName = Name;
			}
			ServerData.PlayerName = SearchResult.Session.OwningUserName;
			ServerData.MaxPlayerNumber = SearchResult.Session.SessionSettings.NumPublicConnections;
			ServerData.CurrentPlayerNumber = ServerData.MaxPlayerNumber - SearchResult.Session.NumOpenPublicConnections;
			ArrayOfServer.Add(ServerData);
		}

		NotifyListeners(ArrayOfServer);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No session found"));
	}
}

void UBZGameInstance::OnJoinSession(FName JoinedSessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!MySessionInterface.IsValid()) { return; }

	if (Result == EOnJoinSessionCompleteResult::Success) {
		FString ConnectInfo = FString();
		if (MySessionInterface->GetResolvedConnectString(JoinedSessionName, ConnectInfo)) {
			APlayerController* playerController = GetFirstLocalPlayerController();
			if (!ensure(playerController != nullptr)) { return; };
			playerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UBZGameInstance::NotifyListeners(TArray<struct FServerData> ArrayOfServer)
{
	for (UBZMainMenu* Listener : Listeners) {
		Listener->PopulateServerDisplayRow(ArrayOfServer);
	}
}

void UBZGameInstance::RegisterListener(UBZMainMenu* inMainMenu)
{
	Listeners.Add(inMainMenu);
}

void UBZGameInstance::Init()
{
	Super::Init();

	// Get the current subsystem
	Subsystem = IOnlineSubsystem::Get();
	if (!ensure(Subsystem != nullptr)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("The online subsystem is %s"), *Subsystem->GetSubsystemName().ToString());

	MySessionInterface = Subsystem->GetSessionInterface();
	if (!ensure(MySessionInterface != nullptr)) { return; };
	UE_LOG(LogTemp, Warning, TEXT("SessionInterface pointer created"));
	if (MySessionInterface.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("SessionInterface is valid"));
	}

	// Add all necessary delegates
	MySessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UBZGameInstance::OnCreateSession);
	MySessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UBZGameInstance::OnDestroySession);
	MySessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UBZGameInstance::OnFindSession);
	MySessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UBZGameInstance::OnJoinSession);
}

void UBZGameInstance::JoinLAN(const FString& ipAddress) {

	// Joining another game at a specific IP address
	UE_LOG(LogTemp, Warning, TEXT("Lan join"));
	APlayerController* player = GetFirstLocalPlayerController();
	if (!ensure(player != nullptr)) { return; }
	player->ClientTravel(*ipAddress, TRAVEL_Absolute, false);
}

void UBZGameInstance::HostLAN() {

	// Hosting a Lan game so that people can join your game at your IP address
	UE_LOG(LogTemp, Warning, TEXT("Host engage"));
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) { return; }
	world->ServerTravel("/Game/Battlezone/Levels/Lobby?listen");
}

void UBZGameInstance::SoloGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Travel to solo level alone"));
	APlayerController* Controller = GetFirstLocalPlayerController();
	Controller->ClientTravel("/Game/Battlezone/Levels/SoloLevel?Game=/Game/Battlezone/CoreBlueprints/BP_SoloGameMode.BP_SoloGameMode_C", TRAVEL_Absolute);
}

void UBZGameInstance::JoinOnline(int32 index)
{
	int32 indexTemp = index - 1;
	if (MySessionInterface.IsValid() && SessionSearchCriteria.IsValid() && SessionSearchCriteria->SearchResults.IsValidIndex(indexTemp)) {
		MySessionInterface->JoinSession(0, MySessionName, SessionSearchCriteria->SearchResults[index-1]);
	}
}

void UBZGameInstance::HostOnline(FString CustomServerName)
{
	CreateGameSession(CustomServerName);
}

void UBZGameInstance::SearchAvailableSessions()
{

	SessionSearchCriteria = MakeShared<FOnlineSessionSearch>();
	if ((Subsystem->GetSubsystemName().ToString()) == "NULL") {
		SessionSearchCriteria->bIsLanQuery = true;
	}
	else {
		SessionSearchCriteria->bIsLanQuery = false;
	}
	SessionSearchCriteria->MaxSearchResults = 10000;
	SessionSearchCriteria->QuerySettings.Set(SearchKey, true, EOnlineComparisonOp::Equals);

	if (SessionSearchCriteria.IsValid()) {
		TSharedRef<FOnlineSessionSearch> SearchCriteriaRef = SessionSearchCriteria.ToSharedRef();
		MySessionInterface->FindSessions(0, SearchCriteriaRef);
	}
}

void UBZGameInstance::LoadMainMenu()
{
	// Based on the class found in the constructor, create a Widget and add it to the viewport
	UE_LOG(LogTemp, Warning, TEXT("LoadMainMenu running"));
	if (!ensure(MainMenuClass != nullptr)) { UE_LOG(LogTemp, Warning, TEXT("LoadMainMenu can't find WBP")); return; };
	UBZMainMenu* MainMenuWidget = CreateWidget<UBZMainMenu>(this, MainMenuClass);

	if (!ensure(MainMenuWidget != nullptr)) { return; };
	MainMenuWidget->AddToViewport();
	UE_LOG(LogTemp, Warning, TEXT("Added to viewport"));

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) { return; };

	// Lock the player's mouse onto the Viewport widget.
	APlayerController* playerController = GetFirstLocalPlayerController(world);
	if (!ensure(playerController != nullptr)) { return; };

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	playerController->SetInputMode(InputMode);
	playerController->bShowMouseCursor = true;

	RegisterListener(MainMenuWidget);
	MainMenuWidget->SetGameInstance(this);
}

void UBZGameInstance::StartLevel()
{
	// Travel with all other players from the Lobby to the match level
	UE_LOG(LogTemp, Warning, TEXT("Travel to match level"));
	SetNumberOfPlayers();
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) { return; }
	world->ServerTravel("/Game/Battlezone/Levels/testLevel?listen");
}

UBZPauseMenu* UBZGameInstance::LoadPauseMenu()
{
	// Based on the class found in the constructor, create a Widget and add it to the viewport
	UE_LOG(LogTemp, Warning, TEXT("LoadPauseMenu running"));
	if (!ensure(MainMenuClass != nullptr)) { UE_LOG(LogTemp, Warning, TEXT("PauseMenu can't find WBP")); return nullptr; };
	UBZPauseMenu* PauseMenuWidget = CreateWidget<UBZPauseMenu>(this, PauseMenuClass);

	if (!ensure(PauseMenuWidget != nullptr)) { return nullptr; };
	PauseMenuWidget->AddToViewport();
	UE_LOG(LogTemp, Warning, TEXT("Added to viewport"));

	PauseMenuWidget->SetGameInstance(this);

	return PauseMenuWidget;
}

void UBZGameInstance::MenuInputMode()
{
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) { return; };

	// Lock the player's mouse onto the Viewport widget.
	APlayerController* playerController = GetFirstLocalPlayerController(world);
	if (!ensure(playerController != nullptr)) { return; };

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	playerController->SetInputMode(InputMode);
	playerController->bShowMouseCursor = true;
}

void UBZGameInstance::GameplayInputMode()
{
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) { return; };

	// Lock the player's mouse onto the Viewport widget.
	APlayerController* playerController = GetFirstLocalPlayerController(world);
	if (!ensure(playerController != nullptr)) { return; };

	FInputModeGameOnly InputMode;
	playerController->SetInputMode(InputMode);
	playerController->bShowMouseCursor = false;
}

int UBZGameInstance::GetNumberOfPlayers()
{
	return numberOfPlayers;
}

void UBZGameInstance::SetNumberOfPlayers()
{
	if (MySessionInterface->GetNamedSession(MySessionName) != NULL) {
		FNamedOnlineSession* Temp = MySessionInterface->GetNamedSession(MySessionName);
		numberOfPlayers = Temp->SessionSettings.NumPublicConnections - Temp->NumOpenPublicConnections;
	}
}

void UBZGameInstance::ReturnMainMenu()
{
	// Hop back to the main menu
	UE_LOG(LogTemp, Warning, TEXT("Going back to MainMenu"));
	APlayerController* player = GetFirstLocalPlayerController();
	if (!ensure(player != nullptr)) { return; }
	player->ClientTravel("/Game/Battlezone/Levels/MainMenuLevel?Game=/Game/Battlezone/CoreBlueprints/BP_BZGameMode.BP_BZGameMode_C", TRAVEL_Absolute, false);
}