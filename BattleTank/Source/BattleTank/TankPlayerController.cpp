// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("I have a tank called %s "), *GetControlledTank()->GetName())

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();


}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank) {
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("I am ticking. "))
	}
}
