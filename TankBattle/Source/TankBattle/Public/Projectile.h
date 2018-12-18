// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class  URadialForceComponent;

UCLASS()
class TANKBATTLE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	UStaticMeshComponent *CollisionMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent *LaunchBlase;

	UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent * ImpactBlast;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent *ExplosionForce;

	void OnTimerExpire();

	UPROPERTY(EditDefaultsOnly, Category = "Set Up")
		float DestroyDelay = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Set Up")
		float ProjectileDamage = 20.0f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float LaunchSpeed);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
