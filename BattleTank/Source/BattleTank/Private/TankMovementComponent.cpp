// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{    
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
   if (!ensure(RightTrack && LeftTrack))
    {
        return;
    }
    
    RightTrack->SetThrottle(Throw);
    LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (!ensure(RightTrack && LeftTrack))
    {
        return;
    }
    
    RightTrack->SetThrottle(-Throw);
    LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{   
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    
    float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    auto TurnCross = FVector::CrossProduct(TankForward, AIForwardIntention);
    
    IntendTurnRight(TurnCross.Z);
    IntendMoveForward(ForwardThrow);
    
}

