// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

class ATank;
class UTankAimingComponent;
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATankPlayerController();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category = "Tank Player Controller")
	ATank* GetControlledTank() const;

	void AimTowardCrosshair();

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation,FVector &LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

private:
	UPROPERTY(EditAnywhere,Category = "ATankPlayerController")
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere, Category = "ATankPlayerController")
		float CrossHairYLocation = 0.3;
	UPROPERTY(EditAnywhere, Category = "ATankPlayerController")
		float LineTraceRange = 100000.f;

protected:
    
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent *AimComRef);

	virtual void BeginPlay() override;
};
