// Fill out your copyright notice in the Description page of Project Settings.


#include "Wepon.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
AWepon::AWepon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);


	Mesh= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void AWepon::BeginPlay()
{
	Super::BeginPlay();
	GetAmmoPercent();
}

// Called every frame
void AWepon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWepon::PullTrigger()
{
	
	FHitResult Hit;
	FVector ShotDirection;

	bool AmmoSucces(AmmoCalculate());
	bool bSuccess(GunTrace(Hit, ShotDirection));

	if (AmmoSucces)
	{

		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("Railgun-PrototypeSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("Railgun-PrototypeSocket"));

		if (bSuccess)
		{

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletHole, Hit.Location, ShotDirection.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

			AActor* HitActor = Hit.GetActor();
			if (HitActor != nullptr)
			{
			FPointDamageEvent DamageEvent(CalculateDamage(), Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
	else
	{
		bIsAmmoOver = true;
		UGameplayStatics::SpawnSoundAttached(DryFire, Mesh, TEXT("Railgun-PrototypeSocket"));
	}
	
}
bool AWepon::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1,Params);
}

AController* AWepon::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn ==nullptr)
		return nullptr;
	return OwnerPawn->GetController();

}

bool AWepon::AmmoCalculate()
{	

	if (Ammos > 1)
	{
		Ammos-= 1;
		UE_LOG(LogTemp, Warning, TEXT("AMMO: %i"), Ammos);
		return true;
	}
	else
	{
		Ammos = 0;
		bIsAmmoOver = true;
		return false;
	}
}

void AWepon::Reload()
{
	if (Clip > 0)
	{
		Clip -= 1;
		Ammos = MaxAmmos;
		bIsAmmoOver = false;
	}
	else
	{
		Clip = 0;
		bIsAmmoOver = true;
	}
}

float AWepon::GetAmmoPercent()
{
	AmmoRatio = Ammos/MaxAmmos;
	UE_LOG(LogTemp, Warning, TEXT("AmmoRatio : %f"), AmmoRatio);
	return AmmoRatio;
}

float AWepon::CalculateDamage()
{
	
	float BaseDamage =FMath::RandRange(23, 28);
	float Crit = FMath::RandRange(0,1);
	if (Crit > 0.9)
	{
		Damage = BaseDamage * 2;
		
	}
	else
	{
		Damage = BaseDamage;
	}
	return Damage;
}
