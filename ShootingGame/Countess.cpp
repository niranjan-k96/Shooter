// Fill out your copyright notice in the Description page of Project Settings.


#include "Countess.h"
#include "Wepon.h"
#include "Components/CapsuleComponent.h"
#include "ShootingGameGameModeBase.h"

// Sets default values
ACountess::ACountess()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void ACountess::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	
	Wepon = GetWorld()->SpawnActor<AWepon>(WeponClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Wepon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	Wepon->SetOwner(this);
}

// Called every frame
void ACountess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACountess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACountess::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACountess::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ACountess::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ACountess::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ACountess::Shoot);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &ACountess::CallReload);

}
float ACountess::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Health : %f"), Health);

	if (IsDead())
	{
		AShootingGameGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShootingGameGameModeBase>();
		if (GameMode != nullptr)

		{
			GameMode->PawnKilled(this);
		}

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();
	}
		return DamageApplied;
}

bool ACountess::IsDead() const
{
	return (Health == 0);
}


void ACountess::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ACountess::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ACountess::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());

}

void ACountess::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ACountess::Shoot()
{
	IsAmmoOver = Wepon->bIsAmmoOver;
	Wepon->PullTrigger();
}

float ACountess::GetHealthPercent()  const
{
	return Health/MaxHealth;
}

float ACountess::GetAmmoPercent()  const
{	
	float AmmoRatio = Wepon->AmmoRatio;
	UE_LOG(LogTemp, Warning, TEXT("AmmoRatio : %f"), AmmoRatio);
	return AmmoRatio;
}