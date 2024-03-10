// Fill out your copyright notice in the Description page of Project Settings.


#include "CRCharacterAnimInstance.h"

#include "PortfolioProject/Core/Characters/CRBaseCharacter.h"
#include "PortfolioProject/Core/Characters/Components/CRCharacterAttributeComponent.h"
#include "PortfolioProject/Core/Characters/Components/CRMovementComponent.h"

void UCRCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CharacterOwner = Cast<ACRBaseCharacter>(TryGetPawnOwner());
}

void UCRCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!CharacterOwner.IsValid())
	{
		return;
	}
	Super::NativeUpdateAnimation(DeltaSeconds);

	UCRMovementComponent* OwnerMovementComponent = CharacterOwner->GetCharacterMovementComponent();
	UCRCharacterAttributeComponent* OwnerAttributes = CharacterOwner->GetAttributeComponent();

	Speed = OwnerMovementComponent->Velocity.Size();
	bIsInAir = OwnerMovementComponent->IsFalling();
	bIsTired = OwnerAttributes->GetIsTired();
	bIsCrouched = CharacterOwner->GetIsCrouching();
	bIsProne=CharacterOwner->GetIsProne();
	
	
	
}
