// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "BZProjectile.generated.h"

UCLASS()
class COSMA272_BATTLEZONE_API ABZProjectile : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Variables
	const float projectileSpeed = 2000.0f;
	const float gravityForce = 1.5f;
	float appliedGravity = 0.0f;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* triggerVolumn;

	// Functions
	ABZProjectile();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
