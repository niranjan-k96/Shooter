// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingGameGameModeBase.h"
#include "KillEmALlGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AKillEmALlGameMode : public AShootingGameGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);

};
