// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/Button.h"
#include "../../../../../../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/UMG/Public/Components/TextBlock.h"
#include "BZServerDisplayRow.generated.h"

/**
 * 
 */
UCLASS()
class COSMA272_BATTLEZONE_API UBZServerDisplayRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Public variables
	FText ServerName;
	FText ServerOwner;
	FText CurrentPlayerNumber;
	FText MaxPlayerNumber;

	// Public function
	void SetUniqueIndex(int serverIndex);
	void SetParent(class UBZMainMenu* mainMenu);
	void SetServerName(FText name);
	void SetServerOwnerName(FText name);
	void SetCurrentAndMaxPlayerNumber(FString current, FString max);
	void setSelected();
	void Deselect();

private:
	// Private variables
	int32 Index;
	class UBZMainMenu* MenuParent;

	// Private function
	bool Initialize();

	UFUNCTION()
	void NotifyParent();

	// BINDINGS

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ServerButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ServerNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OwnerNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerAmountText;
};
