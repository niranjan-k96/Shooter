// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CountessPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API ACountessPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float  RestartDelay = 5;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	UUserWidget* HUD;
};