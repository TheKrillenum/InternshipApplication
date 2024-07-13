// Fill out your copyright notice in the Description page of Project Settings.


#include "BZMainMenu.h"
#include <Kismet/KismetSystemLibrary.h>
#include "UObject/ConstructorHelpers.h"

void UBZMainMenu::SetGameInstance(UBZGameInstance* setter)
{
	gameInstance = setter;
}

UBZMainMenu::UBZMainMenu(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	// Finding and saving the Main Menu class
	ConstructorHelpers::FClassFinder<UBZServerDisplayRow> WBP_ServerDisplayRow(TEXT("/Game/Battlezone/UI/WBP_ServerDisplayRow"));
	if (!ensure(WBP_ServerDisplayRow.Class != nullptr)) { return; }
	ServerDisplayRowClass = WBP_ServerDisplayRow.Class;
	UE_LOG(LogTemp, Warning, TEXT("Widget created: %s"), *ServerDisplayRowClass->GetName());
}

bool UBZMainMenu::Initialize()
{
	if (!Super::Initialize()) { return false; };

	if (!ensure(WidgetSwitcher != nullptr)) { return false; };
	
	// MAIN MENU 
	if (!ensure(SoloGameButton != nullptr)) { return false; };
	SoloGameButton->OnClicked.AddDynamic(this, &UBZMainMenu::SoloGameButtonPressed);

	if (!ensure(SoloGameButton != nullptr)) { return false; };
	LanMultiplayerButton->OnClicked.AddDynamic(this, &UBZMainMenu::LanMultiplayerButtonPressed);

	if (!ensure(SoloGameButton != nullptr)) { return false; };
	OnlineMultiplayerButton->OnClicked.AddDynamic(this, &UBZMainMenu::OnlineMultiplayerButtonPressed);

	if (!ensure(SoloGameButton != nullptr)) { return false; };
	CreditButton->OnClicked.AddDynamic(this, &UBZMainMenu::CreditButtonPressed);

	if (!ensure(SoloGameButton != nullptr)) { return false; };
	QuitButton->OnClicked.AddDynamic(this, &UBZMainMenu::QuitButtonPressed);

	// LAN

	if (!ensure(HostLanButton != nullptr)) { return false; };
	HostLanButton->OnClicked.AddDynamic(this, &UBZMainMenu::HostLanButtonPressed);

	if (!ensure(JoinLanButton != nullptr)) { return false; };
	JoinLanButton->OnClicked.AddDynamic(this, &UBZMainMenu::JoinLanButtonPressed);

	if (!ensure(LanEditableText != nullptr)) { return false; };

	if (!ensure(QuitLanButton != nullptr)) { return false; };
	QuitLanButton->OnClicked.AddDynamic(this, &UBZMainMenu::QuitLanButtonPressed);

	// MULTIPLAYER

	if (!ensure(OnlineSwitcher != nullptr)) { return false; }; 

	if (!ensure(HostOnlineButton != nullptr)) { return false; };
	HostOnlineButton->OnClicked.AddDynamic(this, &UBZMainMenu::HostOnlineButtonPressed);

	if (!ensure(OnlineEditableText != nullptr)) { return false; };

	if (!ensure(JoinOnlineButton != nullptr)) { return false; };
	JoinOnlineButton->OnClicked.AddDynamic(this, &UBZMainMenu::JoinOnlineButtonPressed);

	if (!ensure(QuitOnlineButton != nullptr)) { return false; };
	QuitOnlineButton->OnClicked.AddDynamic(this, &UBZMainMenu::QuitOnlineButtonPressed);

	if (!ensure(JoinServer != nullptr)) { return false; };
	JoinServer->OnClicked.AddDynamic(this, &UBZMainMenu::JoinServerButtonPressed); 

	if (!ensure(QuitJoin != nullptr)) { return false; };
	QuitJoin->OnClicked.AddDynamic(this, &UBZMainMenu::QuitJoinButtonPressed); 

	if(!ensure(ServerDisplayBox != nullptr)) { return false; };

	if (!ensure(ServerVisibility != nullptr)) { return false; };

	// CREDIT

	if (!ensure(QuitCreditButton != nullptr)) { return false; };
	QuitCreditButton->OnClicked.AddDynamic(this, &UBZMainMenu::QuitCreditButtonPressed);

	SelectedIndex = 0;

	SetServerVisibility(false);

	return true;
}

void UBZMainMenu::NativeDestruct()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (!ensure(Controller != nullptr)) { return; };

	FInputModeGameOnly InputMode;
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = false;
	Super::NativeDestruct();
}

void UBZMainMenu::SetServerVisibility(bool bVisibility)
{
	if (!ensure(ServerVisibility != nullptr)) { return; };

	if (bVisibility == true) {

		ServerVisibility->SetVisibility(ESlateVisibility::Visible);
	}
	else {

		ServerVisibility->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBZMainMenu::PopulateServerDisplayRow(TArray<struct FServerData> ServerNames)
{
	int Index = 0;
	if (!arrayOfServers.IsEmpty()) {
		arrayOfServers.Empty();
	}

	for (FServerData ServerData : ServerNames) {
		UBZServerDisplayRow* ServerDisplayRow = CreateWidget<UBZServerDisplayRow>(this, ServerDisplayRowClass);
		if (ServerDisplayRow != nullptr) {
			Index++;
			ServerDisplayRow->SetUniqueIndex(Index);
			ServerDisplayRow->SetParent(this);
			ServerDisplayRow->SetServerName(FText::FromString(ServerData.ServerName));
			ServerDisplayRow->SetServerOwnerName(FText::FromString(ServerData.PlayerName));
			ServerDisplayRow->SetCurrentAndMaxPlayerNumber(FString::FromInt(ServerData.CurrentPlayerNumber), FString::FromInt(ServerData.MaxPlayerNumber));
			if (OnlineSwitcher->GetActiveWidgetIndex() == 1) {
				ServerDisplayBox->AddChild(ServerDisplayRow);
				arrayOfServers.Add(ServerDisplayRow);
			}
			
			UE_LOG(LogTemp, Warning, TEXT("Added server with index: %d"), Index);
		}
	}
}

void UBZMainMenu::SetSelectedIndex(int32 index)
{
	SelectedIndex = index;
	UE_LOG(LogTemp, Warning, TEXT("Selected index equal: %d"), SelectedIndex);
}

void UBZMainMenu::DeselectAllServer()
{
	for (UBZServerDisplayRow* Server : arrayOfServers) {
		Server->Deselect();
	}
}

// MAIN MENU PART 

void UBZMainMenu::SoloGameButtonPressed()
{
	if (!ensure(gameInstance != nullptr)) { return; };
	UE_LOG(LogTemp, Warning, TEXT("Launch  Solo Game"));
	gameInstance->SoloGame();
}

void UBZMainMenu::LanMultiplayerButtonPressed()
{
	if (!ensure(WidgetSwitcher != nullptr)) { return; };
	WidgetSwitcher->SetActiveWidgetIndex(1);
}

void UBZMainMenu::OnlineMultiplayerButtonPressed()
{
	if (!ensure(WidgetSwitcher != nullptr)) { return; };
	OnlineSwitcher->SetActiveWidgetIndex(0);
	WidgetSwitcher->SetActiveWidgetIndex(2);
}

void UBZMainMenu::CreditButtonPressed()
{
	if (!ensure(WidgetSwitcher != nullptr)) { return; };
	WidgetSwitcher->SetActiveWidgetIndex(3);
}

void UBZMainMenu::QuitButtonPressed()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; };
	UKismetSystemLibrary::QuitGame(World, 0, EQuitPreference::Quit, false);
}

// LAN PART

void UBZMainMenu::HostLanButtonPressed()
{
	if (!ensure(gameInstance != nullptr)) { return; };
	UE_LOG(LogTemp, Warning, TEXT("Host Lan"));
	gameInstance->HostLAN();
}

void UBZMainMenu::JoinLanButtonPressed()
{
	if (!ensure(gameInstance != nullptr)) { return; };
	UE_LOG(LogTemp, Warning, TEXT("Join Lan"));
	gameInstance->JoinLAN(LanEditableText->GetText().ToString());
}

void UBZMainMenu::QuitLanButtonPressed()
{
	if (!ensure(WidgetSwitcher != nullptr)) { return; };
	WidgetSwitcher->SetActiveWidgetIndex(0);
}

// MULTIPLLAYER PART

void UBZMainMenu::HostOnlineButtonPressed()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Host online"));

	if (!ensure(OnlineEditableText != nullptr)) { return; };
	FString temp = OnlineEditableText->GetText().ToString();

	if (!ensure(gameInstance != nullptr)) { return; };
	gameInstance->HostOnline(temp);
}

void UBZMainMenu::JoinOnlineButtonPressed()
{
	gameInstance->SearchAvailableSessions();
	SelectedIndex = 0;
	SetServerVisibility(true);
	OnlineSwitcher->SetActiveWidgetIndex(1);
}

void UBZMainMenu::QuitOnlineButtonPressed()
{
	if (!ensure(WidgetSwitcher != nullptr)) { return; };
	WidgetSwitcher->SetActiveWidgetIndex(0);
	
}

void UBZMainMenu::JoinServerButtonPressed()
{
	if (!ensure(gameInstance != nullptr)) { return; };
	UE_LOG(LogTemp, Warning, TEXT("Join Online"));
	gameInstance->JoinOnline(SelectedIndex);
	UE_LOG(LogTemp, Warning, TEXT("Wait"));
}

void UBZMainMenu::QuitJoinButtonPressed()
{
	SelectedIndex = 0;
	SetServerVisibility(false);
	ServerDisplayBox->ClearChildren();
	OnlineSwitcher->SetActiveWidgetIndex(0);
}

// CREDIT PART

void UBZMainMenu::QuitCreditButtonPressed()
{
	if (!ensure(WidgetSwitcher != nullptr)) { return; };
	WidgetSwitcher->SetActiveWidgetIndex(0);
}