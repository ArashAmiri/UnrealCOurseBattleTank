// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;

	void Tick(float) override;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
		int LINE_TRACE_RANGE = 1500000;

private:

	void AimTowardsCrossHair();

	bool GetSightRateHitLocation(FVector &);

	FVector2D FindCrossHairLocationOnScreen();

	bool GetLookDirection(FVector & LookDirection);

};
