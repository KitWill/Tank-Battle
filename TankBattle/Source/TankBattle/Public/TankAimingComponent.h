// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"



class UTankBarrel;
class UTankTurret;


UENUM()
enum  class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UTankAimingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector WorldSpaceAim);

	void MoveBarrelToward(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = "Movement Component")
		void Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Tank")
		void Fire();

	
	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetGoundLeft() const;
	 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Tank Aiming Component")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 100000.0f;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ReloadTimeInSeconds = 3;
	float LastFireTime = 0;

	FVector AimDirection = FVector(0,0,0);

	bool IsBarrelMoving();
	
public:	

	UTankBarrel *Barrel;
	UTankTurret *Turret;
	int RoundsLeft = 3;

};
