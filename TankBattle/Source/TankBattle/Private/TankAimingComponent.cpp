// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!Barrel || !Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSoution =UGameplayStatics::SuggestProjectileVelocity
	   (this,
		OutLaunchVelocity,
		StartLocation, 
		WorldSpaceAim, 
		LaunchSpeed,
		false,
	    0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

    if(bHaveAimSoution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
	}	

}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	auto BarrleRotatior = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotaror = AimAsRotator - BarrleRotatior;
	Barrel->Elevate(DeltaRotaror.Pitch);
	Turret->Rotate(DeltaRotaror.Yaw);
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (GetWorld()->TimeSeconds - LastFireTime) > ReloadTimeInSeconds;
	if (!Barrel || !ProjectileBlueprint)
	{
		//TODO Log erro
		return;
	}
	if(isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,Barrel->GetSocketLocation(FName("Projectile")),Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
	}
}