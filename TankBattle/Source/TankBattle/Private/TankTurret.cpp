// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotateChange = RelativeSpeed * MaxDegreesPerSencond * GetWorld()->DeltaTimeSeconds;
	auto NewRotate = RelativeRotation.Yaw + RotateChange;
	SetRelativeRotation(FRotator(0, NewRotate, 0));
}

