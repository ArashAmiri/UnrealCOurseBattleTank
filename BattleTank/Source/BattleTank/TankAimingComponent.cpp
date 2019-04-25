// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (this->Barrel && this->Turret) {

		FVector OutTossVelocity(0);
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		
		TArray<AActor *> ActorsToIgnore;
		ActorsToIgnore.Reset();
		
		bool SuccessFullyCalculatedVelocity = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OUT OutTossVelocity,
			StartLocation,
			TargetLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		float TimeSeconds = GetWorld()->GetTimeSeconds();

		if (SuccessFullyCalculatedVelocity) {
			FVector NormalizedTossVelocity = OutTossVelocity.GetSafeNormal();
			FString BarrelLocation = this->Barrel->GetComponentLocation().ToString();

			MoveBarrel(NormalizedTossVelocity);
		}
		
	}

}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::MoveBarrel(FVector AimVector)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimVector.Rotation();

	float DesiredPitch = AimRotation.Pitch - BarrelRotation.Pitch;
	float DesiredYaw = AimRotation.Yaw - BarrelRotation.Yaw;

	UE_LOG(LogTemp, Error, TEXT("Desired Yaw == %f "), DesiredYaw)

	Barrel->Elevate(DesiredPitch);
	Turret->Rotate(DesiredYaw);
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	this->Barrel = BarrelToSet;	

}

void UTankAimingComponent::SetTurret(UTankTurret * TurretToSet)
{
	this->Turret = TurretToSet;
}

