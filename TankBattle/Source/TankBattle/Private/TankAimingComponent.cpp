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
	LastFireTime = GetWorld()->TimeSeconds;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	auto BarrelFoeward = Barrel->GetForwardVector();
	return !BarrelFoeward.Equals(AimDirection, 0.01);
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (RoundsLeft <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->TimeSeconds - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
	
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
	    AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
	}	

}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	auto BarrleRotatior = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotaror = AimAsRotator - BarrleRotatior;
	Barrel->Elevate(DeltaRotaror.Pitch);

	if (DeltaRotaror.Yaw < 180)
	{
		Turret->Rotate(DeltaRotaror.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotaror.Yaw);
	}
	
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	if(FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::OutOfAmmo)
	{
		if (!ensure(Barrel)) return;
		if (!ensure(ProjectileBlueprint))return;
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,Barrel->GetSocketLocation(FName("Projectile")),Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->TimeSeconds;
		RoundsLeft--;
	}
	
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetGoundLeft() const
{
	return RoundsLeft;
}
