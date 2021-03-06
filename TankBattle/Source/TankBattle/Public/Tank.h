// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

class UCameraComponent;

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
	
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure,Category = "Health")
	float GetHealthPercentage() const;

//	UTankBarrel *Barrel = nullptr;

	UCameraComponent *ThirdCam;
	UCameraComponent *FirstCam;

	/*UPROPERTY(BlueprintReadOnly, Category = "Tank Movement")
	UTankMovementComponent *TankMovementComponent;*/
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTankDelegate OnDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Set Up")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Set Up")
	int32 CurrentHealth;

	UFUNCTION(BlueprintCallable, Category = "Camera Switch")
		void SwitchCamera();


};
