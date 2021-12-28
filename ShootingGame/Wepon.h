// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Countess.h"
#include "Wepon.generated.h"



UCLASS()
class SHOOTINGGAME_API AWepon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWepon();

	UFUNCTION(BlueprintCallable)
	void PullTrigger();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	float GetAmmoPercent();

	UFUNCTION()
	float CalculateDamage();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAmmoOver = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Clip = 5;
	
	UPROPERTY(EditAnywhere)
	float MaxAmmos = 10;

	UPROPERTY(BlueprintReadWrite)
	float Ammos= MaxAmmos;

	UPROPERTY(BlueprintReadOnly)
	float AmmoRatio;


private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* DryFire;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	UParticleSystem* BulletHole;

	UPROPERTY(EditAnywhere)
	USoundBase *ImpactSound;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	bool AmmoCalculate();

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
