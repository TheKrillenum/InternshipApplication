// Fill out your copyright notice in the Description page of Project Settings.


#include "BZServerDisplayRow.h"
#include "BZMainMenu.h"

bool UBZServerDisplayRow::Initialize()
{
	if (!Super::Initialize()) { return false; };

	if (!ensure(ServerNameText != nullptr)) { return false; };

	if (!ensure(OwnerNameText != nullptr)) { return false; };

	if (!ensure(PlayerAmountText != nullptr)) { return false; };

	if (!ensure(ServerButton != nullptr)) { return false; };
	ServerButton->OnClicked.AddDynamic(this, &UBZServerDisplayRow::NotifyParent);

	return true;
}

void UBZServerDisplayRow::NotifyParent()
{
	if (!ensure(MenuParent != nullptr)) { return; }
	MenuParent->SetSelectedIndex(Index);
	setSelected();
}

void UBZServerDisplayRow::SetUniqueIndex(int serverIndex)
{
	if (serverIndex != 0) {
		Index = serverIndex;
	}
}

void UBZServerDisplayRow::SetParent(UBZMainMenu* mainMenu)
{
	if (!ensure(mainMenu != nullptr)) { return; }
	MenuParent = mainMenu;
}

void UBZServerDisplayRow::SetServerName(FText name)
{
	if (!ensure(ServerNameText != nullptr)) { return; }
	ServerName = name;
	ServerNameText->SetText(ServerName);
}

void UBZServerDisplayRow::SetServerOwnerName(FText name)
{
	if (!ensure(OwnerNameText != nullptr)) { return; }
	ServerOwner = name;
	OwnerNameText->SetText(ServerOwner);
}

void UBZServerDisplayRow::SetCurrentAndMaxPlayerNumber(FString current, FString max)
{
	if (!ensure(PlayerAmountText != nullptr)) { return; }

	FString temp;
	temp = current + FString(" / ") + max;
	PlayerAmountText->SetText(FText::FromString(temp));
}

void UBZServerDisplayRow::setSelected()
{
	MenuParent->DeselectAllServer();
	ServerButton->SetBackgroundColor(FLinearColor(0.427083, 1.0, 0.492681));
}

void UBZServerDisplayRow::Deselect()
{
	ServerButton->SetBackgroundColor(FLinearColor(0.516667, 0.516667, 0.516667));
}
