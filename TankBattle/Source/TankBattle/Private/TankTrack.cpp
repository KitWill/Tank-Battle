// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpwanPoint.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent *> Children;
	GetChildrenComponents(true, Children);

	for(USceneComponent * Child:Children)
	{
		auto SpwanPiont = Cast<USpwanPoint>(Child);
		if (!SpwanPiont) continue;

		AActor *SpawnedChild = SpwanPiont->GetSpwanedActor();

		auto SpawnedWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SpawnedWheel) continue;

		ResultArray.Add(SpawnedWheel);
	}

	return ResultArray;
}


void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottel = FMath::Clamp( Throttle, -1.0f, 1.0f);
	DriveTrack(CurrentThrottel);
}

void UTankTrack::DriveTrack(float CurrentThrottel)
{
	auto ForceApplied = CurrentThrottel*TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel *Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
	
}


