// Fill out your copyright notice in the Description page of Project Settings.


#include "EnenmyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Countess.h"

void AEnenmyAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AIBehavior != nullptr)

	{
		RunBehaviorTree(AIBehavior);
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
	
	
}

void AEnenmyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AEnenmyAIController::IsDead() const
{
	ACountess* ControlledCharacter = Cast<ACountess>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}