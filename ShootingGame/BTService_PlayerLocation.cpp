// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Kismet/Gameplaystatics.h"
#include "GameFramework/Pawn.h"


UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("UpdatePlayerLocation");

}
void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn == nullptr)
	{
		return;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
