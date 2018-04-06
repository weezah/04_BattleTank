// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
   
    
	if (!ensure(PlayerTank) || !ensure(AimingComponent))
        return;
    
    // TODO Move towards the player
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    // Aim towards the player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    AimingComponent->Fire(); // TODO limit firing rate

}
