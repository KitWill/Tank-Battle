// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class UTankBarrel;
class UTankTurret;


UENUM()
enum  class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UTankAimingComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

	void MoveBarrelToward(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = "Movement Component")
		void Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Tank Aiming Component")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;
	
public:	

	UTankBarrel *Barrel;
	UTankTurret *Turret;

};
