// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
private:

	UTankTrack *LeftTrack;
	UTankTrack *RightTrack;

	UFUNCTION(BlueprintCallable, Category = "Movement Component")
	void Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);

public:
	UFUNCTION(BlueprintCallable, Category = "Movement Component")
	    void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Movement Component")
		void IntendTurnRight(float Throw);
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
};
