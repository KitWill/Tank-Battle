// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */

class ASprungWheel;

UCLASS(meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottel);
	
	UPROPERTY(EditDefaultsOnly, Category = "Track")
		float TrackMaxDrivingForce = 400000;

	virtual void BeginPlay() override;

private:

	TArray<ASprungWheel *> GetWheels() const;

};
