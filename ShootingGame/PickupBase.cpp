// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollissionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollissionVolume"));
	RootComponent = CollissionVolume;

	Mesh=  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	

	CollissionVolume->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::BeginOverlap);
	CollissionVolume->OnComponentEndOverlap.AddDynamic(this, &APickupBase::EndOverlap);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::On Overlap Begin"));
}

void APickupBase::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Super::On Overlap End"));
}

