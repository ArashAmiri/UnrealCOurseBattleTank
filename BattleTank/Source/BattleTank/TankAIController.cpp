// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankAIController::Tick(float DeltaTime)
{

	
	Super::Tick(DeltaTime);
	
	ATank * PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No player tank found. "));
	}
	
}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();


	ATank* PlayerTank = GetPlayerTank();

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

