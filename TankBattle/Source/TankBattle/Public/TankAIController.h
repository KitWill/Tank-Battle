// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ATankAIController();

	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Track")
		float AcceptanceRadius = 3000;

	UFUNCTION()
	void OnPossedTankDeath();
};
