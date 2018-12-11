// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"



ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		FVector HitLocation = GetPlayerTank()->GetActorLocation();
		GetControlledTank()->AimAt(HitLocation);

		MoveToActor(GetPlayerTank(), AcceptanceRadius);
		GetControlledTank()->Fire();
	}
}

ATank*  ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	} 
	return Cast<ATank>(PlayerPawn);
}

