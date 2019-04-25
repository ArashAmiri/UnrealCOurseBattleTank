// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "CoreMinimal.h"


void UTankBarrel::Elevate(float RelativeSpeed) {

	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}