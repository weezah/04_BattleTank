// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
};

// Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);
    
    UFUNCTION(BlueprintCallable, Category = Firing)
    void Fire();
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:    
    UPROPERTY(BlueprintReadOnly, Category = Firing)
    EFiringState FiringStatus = EFiringState::Reloading;
    
    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;

    
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float LaunchSpeed = 4000;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTimeInSeconds = 3;
    double LastFireTime = 0;

};
