// Fill out your copyright notice in the Description page of Project Settings.

#define OUT

#include "Tank.h"
#include "Engine/World.h"
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
	FVector HitLocation;
	bool HitSomething = GetSightRateHitLocation(OUT HitLocation);
		
	if (HitSomething) {
		UE_LOG(LogTemp, Warning, TEXT("OutLocation is Something: %s"), *HitLocation.ToString())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nothing Hit."))
	}
}

bool ATankPlayerController::GetSightRateHitLocation(FVector &OutHitLocation)
{
	ATank* ControlledTank = GetControlledTank();

	if (ControlledTank) {

		FVector2D CrossHairLocationOnScreen = FindCrossHairLocationOnScreen();
		UE_LOG(LogTemp, Error, TEXT("CrossHairLocationOnScreen = %s."), *CrossHairLocationOnScreen.ToString())

		FVector StartLocation = GetControlledTank()->GetActorLocation();
		FVector EndLocation = GetControlledTank()->GetActorLocation();

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(OUT HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
		if (HitResult.GetActor()) {
			OutHitLocation = HitResult.GetActor()->GetActorLocation();
			return true;
		}
	}

	return false;
}

FVector2D ATankPlayerController::FindCrossHairLocationOnScreen()
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(OUT ViewPortSizeX, OUT ViewPortSizeY);

	UE_LOG(LogTemp, Error, TEXT("ViewPortSizeX = %s. ViewPortSizeY = %s "), *FString::FromInt(ViewPortSizeX), *FString::FromInt(ViewPortSizeY))

	FVector2D Result;
	Result.X = ViewPortSizeX * CrossHairXLocation;
	Result.Y = ViewPortSizeY * CrossHairYLocation;

	return Result;
}
