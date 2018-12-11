// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack|| !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(-Throw);
}

 void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	 auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	 auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	 auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention); //求出TankForward与AIForwardIntention的Cos值，用这来决定AITank是否向前或向后走
	 IntendMoveForward(ForwardThrow);

	 auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	 IntendTurnRight(RightThrow);
}