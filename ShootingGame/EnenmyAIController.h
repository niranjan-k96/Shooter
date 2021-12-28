// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnenmyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AEnenmyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;


	
};
