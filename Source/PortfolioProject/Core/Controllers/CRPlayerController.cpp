// Fill out your copyright notice in the Description page of Project Settings.


#include "CRPlayerController.h"

#include "PortfolioProject/Core/Characters/CRBaseCharacter.h"
#include "PortfolioProject/Core/Characters/Components/CRMovementComponent.h"

void ACRPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	
	
	CharacterOwner=Cast<ACRBaseCharacter>(InPawn);	
	
}

void ACRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ACRPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACRPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACRPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &ACRPlayerController::LookUp);

	InputComponent->BindAction("Sprint", IE_Pressed, this , &ACRPlayerController::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this , &ACRPlayerController::EndSprint);


	
}

void ACRPlayerController::MoveForward(float Value)
{
	if (CharacterOwner)
	{
		CharacterOwner->MoveForward(Value);

	}
}

void ACRPlayerController::MoveRight(float Value)
{
	if (CharacterOwner)
	{
		CharacterOwner->MoveRight(Value);
	}
}

void ACRPlayerController::Turn(float Value)
{
	if (CharacterOwner)
	{
		CharacterOwner->Turn(Value);
	}
}

void ACRPlayerController::LookUp(float Value)
{
	if (CharacterOwner)
	{
		CharacterOwner->LookUp(Value);
	}
}

void ACRPlayerController::StartSprint()
{
	if (CharacterOwner)
	{
		CharacterOwner->ChangeSprintCondition(true);
	}
}

void ACRPlayerController::EndSprint()
{
	if (CharacterOwner)
	{
		CharacterOwner->ChangeSprintCondition(false);
	}
}

void ACRPlayerController::Sprint(bool bIsSprinting)
{
	if (CharacterOwner)
	{
		
	}
	
}

