// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpwanPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API USpwanPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpwanPoint();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor *GetSpwanedActor() const { return SpwanedActor; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;			

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;
	
	UPROPERTY()
	AActor *SpwanedActor;

};
