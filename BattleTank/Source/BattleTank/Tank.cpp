// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "CoreMinimal.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//Barrel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Barrel"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector TargetLocation)
{
	TankAimingComponent->AimAt(TargetLocation, this->LaunchSpeed);

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrel(BarrelToSet);
	this->Barrel = BarrelToSet;
	
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurret(TurretToSet);
}

void ATank::setTankTrackLeftReference(UTankTrack * TankTrackToSet)
{
	this->TankTrackLeft = TankTrackToSet;
}

void ATank::setTankTrackRightReference(UTankTrack * TankTrackToSet)
{
	this->TankTrackRight = TankTrackToSet;
}

void ATank::Fire()
{
	bool isReloaded = GetWorld()->GetRealTimeSeconds() - ReloadTimeInSeconds > LastFireTime;

	if (Barrel && isReloaded) {
		FName PROJECTILE_SOCKET_NAME = FName("Projectile");
		FVector SocketLocation = Barrel->GetSocketLocation(PROJECTILE_SOCKET_NAME);
		FRotator SocketRotation = Barrel->GetSocketRotation(PROJECTILE_SOCKET_NAME);
		auto *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, SocketLocation, SocketRotation);
		Projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetRealTimeSeconds();
	}





}



