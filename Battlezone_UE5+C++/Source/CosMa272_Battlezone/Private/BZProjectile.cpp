// Fill out your copyright notice in the Description page of Project Settings.


#include "BZProjectile.h"

// Sets default values
ABZProjectile::ABZProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerVolumn = CreateDefaultSubobject<USphereComponent>(TEXT("C++SphereCollision"));
	if (!ensure(triggerVolumn != nullptr)) { return; }
	
	triggerVolumn->SetNotifyRigidBodyCollision(true);
	triggerVolumn->OnComponentBeginOverlap.AddDynamic(this, &ABZProjectile::OnSphereOverlap);
	RootComponent = triggerVolumn;
}

// Called when the game starts or when spawned
void ABZProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
	}

}

// Called every frame
void ABZProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasAuthority()) {
		FVector temp = GetActorLocation();
		temp += GetActorForwardVector() * projectileSpeed * DeltaTime;
		appliedGravity += (gravityForce * DeltaTime);
		temp.Z -= appliedGravity;

		SetActorLocation(temp);
	}
}

void ABZProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
}