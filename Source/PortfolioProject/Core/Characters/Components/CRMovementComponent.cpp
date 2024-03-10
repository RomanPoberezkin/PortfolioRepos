// Fill out your copyright notice in the Description page of Project Settings.


#include "CRMovementComponent.h"

#include "CRCharacterAttributeComponent.h"

float UCRMovementComponent::GetMaxSpeed() const
{
	float Result = Super::GetMaxSpeed();

	if (bIsWalking)
	{
		Result=CurrentWalkingSpeed;
	}
	if (bIsCrouching)
	{
		Result=CurrentCrouchingSpeed;
	}
	if (bIsSprinting)
	{
		Result=CurrentSprintSpeed;
	}
	if (bIsTired)
	{
		Result = CurrentTiredSpeed;
	}
	if (bIsProne)
	{
		Result=CurrentProneSpeed;
	}
	

	return Result;

}

void UCRMovementComponent::ChangeSprintCondition(bool IsSprinting, float NewSpeed)
{
	
	bIsSprinting=IsSprinting;
	bIsWalking=!IsSprinting;
	if (IsSprinting)
	{
		CurrentSprintSpeed = NewSpeed;
	}
	else
	{
		CurrentWalkingSpeed=NewSpeed;
	}
	
}

void UCRMovementComponent::SetDefaultMaxWalkSpeed(float NewSpeed)
{	
	MaxWalkSpeed=NewSpeed;
	BaseWalkSpeed=MaxWalkSpeed;
	CurrentWalkingSpeed=NewSpeed;
}

void UCRMovementComponent::ChangeTiredCondition(bool IsTired, float NewWalkSpeed)
{
	bIsTired=IsTired;
	
	bIsWalking=!IsTired;
	
	if (IsTired)
	{
		CurrentTiredSpeed = NewWalkSpeed;
	}
	else
	{
		CurrentWalkingSpeed=NewWalkSpeed;
	}
}

void UCRMovementComponent::StartCrouching(float NewWalkSpeed)
{
	bIsCrouching=true;
	bIsWalking=false;
	CurrentCrouchingSpeed=NewWalkSpeed;
}

void UCRMovementComponent::EndCrouching(float NewWalkSpeed)
{
	bIsCrouching=false;
	bIsWalking=true;
	CurrentWalkingSpeed=NewWalkSpeed;
}

void UCRMovementComponent::StartProne(float NewWalkSpeed)
{
	bIsCrouching=false;
	bIsProne = true;
	bIsWalking=false;
	CurrentProneSpeed = NewWalkSpeed;
}

void UCRMovementComponent::EndProne(float NewWalkSpeed)
{
	bIsProne=false;
	bIsWalking=true;
	CurrentWalkingSpeed = NewWalkSpeed;
}

