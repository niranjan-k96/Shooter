// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "Expoloive.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AExpoloive : public APickupBase
{
	GENERATED_BODY()
	
public:
	AExpoloive();

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)override;
};
