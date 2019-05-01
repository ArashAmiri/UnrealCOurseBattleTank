// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::IntentMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) {
		return;
	}
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

void UTankMovementComponent::initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	this->LeftTrack = LeftTrackToSet;
	this->RightTrack = RightTrackToSet;
}

