// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "Actor.h"
#include "Kismet/GameplayStatics.h"

AAmmoPickup::AAmmoPickup()
{
	
}


void AAmmoPickup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	Wepon = Countess->Wepon;

	if (OtherActor == Countess)
	{
		UE_LOG(LogTemp, Warning, TEXT("COunteess overlapped"));
		Wepon->Clip += 1;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
		Destroy();

		return;
	}
	
	
}

void AAmmoPickup::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::EndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("Explosive::On Overlap End"));
}

void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
	Countess = Cast<ACountess>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Wepon = Countess->Wepon;
}
