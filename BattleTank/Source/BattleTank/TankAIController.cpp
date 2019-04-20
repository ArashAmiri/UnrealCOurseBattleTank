// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	ATank* ControlledTank = GetControlledTank();

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("I, the AIController, have a tank called %s "), *GetControlledTank()->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("I, the AIController, control no tank..."))
	}

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("I, the AIController, have found the players tank called %s"), *PlayerTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("I, the AIController, have found no player tank..."))
	}

}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto *PlayerController = GetWorld()->GetFirstPlayerController();
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(PlayerController);
	return TankPlayerController->GetControlledTank();
}
