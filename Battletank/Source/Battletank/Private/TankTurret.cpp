// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{

	// -1 is max downward movement, and +1 is max up movement
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	auto NewRotation = RawNewRotation;
	

	/*auto timestamp = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Turret Rotation %f"), timestamp, NewRotation);*/
	SetRelativeRotation(FRotator(0, NewRotation, 0));

}


