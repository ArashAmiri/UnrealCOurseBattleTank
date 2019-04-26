// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeYaw) {

	float ClampedRelativeYaw = FMath::Clamp<float>(RelativeYaw, -1, 1);
	auto RotationChange = ClampedRelativeYaw * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float TurretRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, TurretRotation, 0));
}

