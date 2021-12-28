// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Countess.h"
#include "PickupBase.h"
#include "Wepon.h"
#include "AmmoPickup.generated.h"
/**
 *
 */

UCLASS()
class SHOOTINGGAME_API AAmmoPickup : public APickupBase
{
	GENERATED_BODY()

public:
	AAmmoPickup();

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)override;
	
private:
	ACountess* Countess;

	AWepon* Wepon;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
