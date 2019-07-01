// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntentMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Setting throwttle!!!!"))
	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) {
		return;
	}
	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & Velocity, bool MaxForceSpeed)
{
	//No need to call super as we are replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = Velocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	//IntentMoveForward(ForwardThrow);
}

void UTankMovementComponent::initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	this->LeftTrack = LeftTrackToSet;
	this->RightTrack = RightTrackToSet;
}

