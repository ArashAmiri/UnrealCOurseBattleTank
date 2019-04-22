// Fill out your copyright notice in the Description page of Project Settings.

#define OUT

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRateHitLocation(FVector &OutHitLocation)
{
		FVector LookDirection;
		if (GetLookDirection(OUT LookDirection)) {

			ATank* ControlledTank = GetControlledTank();

			if (ControlledTank) {
				TArray<AActor *> AttachedActors;
				GetAttachedActors(OUT AttachedActors);

				FVector LineStart = PlayerCameraManager->GetCameraLocation();				
				FVector LineEnd = LineStart + (LookDirection * LINE_TRACE_RANGE);

				FHitResult HitResult;

				GetWorld()->LineTraceSingleByChannel(OUT HitResult, LineStart, LineEnd, ECollisionChannel::ECC_Visibility);

				if (HitResult.GetActor()) {
					OutHitLocation = HitResult.Location;
					return true;
				}
				else {
					OutHitLocation = FVector(0);
				}
				
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("No controlled tank "));

			}

		}
		return false;

}

FVector2D ATankPlayerController::FindCrossHairLocationOnScreen()
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(OUT ViewPortSizeX, OUT ViewPortSizeY);

	FVector2D Result;
	Result.X = ViewPortSizeX * CrossHairXLocation;
	Result.Y = ViewPortSizeY * CrossHairYLocation;

	return Result;
}

bool ATankPlayerController::GetLookDirection(FVector & LookDirection)
{
	FVector2D CrossHairLocationOnScreen = FindCrossHairLocationOnScreen();
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(CrossHairLocationOnScreen.X, CrossHairLocationOnScreen.Y, WorldLocation, OUT LookDirection);
}
