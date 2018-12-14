// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankAimingComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000.0f;

//	UTankBarrel *Barrel = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Tank Movement")
	UTankAimingComponent * TankAimingComponent;

	/*UPROPERTY(BlueprintReadOnly, Category = "Tank Movement")
	UTankMovementComponent *TankMovementComponent;*/

public:
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTimeInSeconds = 3;
	float LastFireTime = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector &HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Tank")
		void Fire();
};
