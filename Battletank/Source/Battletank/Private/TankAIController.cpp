// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AimTowardsCrosshair();
	if (TargetTank) {
		GetControlledTank()->AimAt(TargetTank->GetActorLocation());
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("No player tank controlled"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controlled tank: %s"), *(PlayerTank->GetName()));
	}
	TargetTank = GetPlayerTank();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}
