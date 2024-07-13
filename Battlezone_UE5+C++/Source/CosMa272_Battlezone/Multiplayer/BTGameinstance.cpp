// Fill out your copyright notice in the Description page of Project Settings.


#include "BTGameinstance.h"

UBTGameinstance::UBTGameinstance()
{
	//creating the main menu class
	ConstructorHelpers::FClassFinder<UUserWidget> WBPMainMenu(TEXT("/Game/Battlezone/UI/WBP_MainMenu"));
	if (!ensure(WBPMainMenu.Class != nullptr)) { return; }
	MainMenu = WBPMainMenu.Class;
	UE_LOG(LogTemp, Warning, TEXT("Widget created: "), *MainMenu->GetName());
}

void UBTGameinstance::Init()
{
	Super::Init();
}

void UBTGameinstance::Join() {
	UE_LOG(LogTemp, Warning, TEXT("Join yo"));
	APlayerController* player = GetFirstLocalPlayerController();
	if (!ensure(player != nullptr)) { return; }
	player->ClientTravel(ipAddress, TRAVEL_Absolute, false);
}

void UBTGameinstance::Host() {
	UE_LOG(LogTemp, Warning, TEXT("Host engage"));
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) { return; }
	world->ServerTravel("/Game/FirstPerson/Maps/FirstPersonMap?listen");
}