// Fill out your copyright notice in the Description page of Project Settings.


#include "CRMovementComponent.h"

void UCRMovementComponent::ChangeSprintCondition(bool bIsSprinting, float NewSpeed)
{
	
	bIsSprintingCondition=bIsSprinting;
	MaxWalkSpeed = NewSpeed;
	

	//TODO Add Stamina use function delegate
}

void UCRMovementComponent::SetDefaultMaxWalkSpeed(float NewSpeed)
{
	
	MaxWalkSpeed=NewSpeed;
	BaseWalkSpeed=MaxWalkSpeed;
}
