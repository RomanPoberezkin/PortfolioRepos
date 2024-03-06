// Fill out your copyright notice in the Description page of Project Settings.


#include "CRMovementComponent.h"

void UCRMovementComponent::ChangeSprintCondition(bool bIsSprinting)
{
	
	bIsSprintingCondition=bIsSprinting;
	float NewSpeed = bIsSprinting ? MaxWalkSpeed + SprintSpeedDelta : MaxWalkSpeed -SprintSpeedDelta;
	MaxWalkSpeed =NewSpeed;	
}
