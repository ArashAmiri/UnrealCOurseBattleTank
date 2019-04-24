// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"


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
	if (this->Barrel) {

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
			ESuggestProjVelocityTraceOption::DoNotTrace
		);


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
	FRotator DesiredRotation = BarrelRotation - AimRotation;

	Barrel->Elevate(5);
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

