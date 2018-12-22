// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class TANKBATTLE_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent *Wheel;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent *Axle;

	UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent *MassWheelConstraint;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent *AxleWheelConstraint;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void SetupConstraint();

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;
	
};
