// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);


	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerTank && ControlledTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No player tank found. "));
	}
	
}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

