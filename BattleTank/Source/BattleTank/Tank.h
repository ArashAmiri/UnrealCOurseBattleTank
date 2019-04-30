// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class UTankTrack;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector TargetLocation);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileToSpawn;

	//************ FUNCTIONS **********************

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTankTrackLeftReference(UTankTrack* TankTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTankTrackRightReference(UTankTrack* TankTrackToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent *TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent *TankMovementComponent = nullptr;


private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UTankBarrel *Barrel = nullptr;
	UTankTrack *TankTrackLeft;
	UTankTrack *TankTrackRight;

	float ReloadTimeInSeconds = 3;
	float LastFireTime = 0;

};
