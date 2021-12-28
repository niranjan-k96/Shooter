// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmALlGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "EnenmyAICOntroller.h"

void AKillEmALlGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for (AEnenmyAIController* AIController : TActorRange<AEnenmyAIController>(GetWorld()))
	{
		if (!AIController ->IsDead())
		{
			return;
		}

	}
	EndGame(true);
}

void AKillEmALlGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}