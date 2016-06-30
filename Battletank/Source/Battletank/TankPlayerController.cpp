// Fill out your copyright notice in the Description page of Project Settings.


#include "Battletank.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No tank controlled"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank controlled: %s"), *(ControlledTank->GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }


	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	int ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);


	//	float CrosshairScreenLocationX, CrosshairScreenLocationY;

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;

	//	FVector2D 
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		
		GetTargetNameLocation(LookDirection, HitLocation);
	}

	return true;
}
bool ATankPlayerController::GetTargetNameLocation(FVector Direction, FVector& HitLocation) const
{
	FHitResult OutHit;
	FVector Start = PlayerCameraManager->GetCameraLocation(), End;


	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility;
	GetWorld()->LineTraceSingleByChannel(
		OutHit,
		Start,
		Start + Direction * LineTraceRange,
		TraceChannel);

	if (OutHit.bBlockingHit) {
		HitLocation = OutHit.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;


}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);


}