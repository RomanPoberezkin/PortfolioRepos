// Fill out your copyright notice in the Description page of Project Settings.


#include "CRCharacterAttributeComponent.h"

#include "CRMovementComponent.h"
#include "PortfolioProject/Core/Characters/CRBaseCharacter.h"


// Sets default values for this component's properties
UCRCharacterAttributeComponent::UCRCharacterAttributeComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	
	CharacterOwner=Cast<ACRBaseCharacter>(GetOwner());
	
	if (CharacterOwner.IsValid())
	{
		OwnerMovementComponent=Cast<UCRMovementComponent>(CharacterOwner->GetCharacterMovementComponent());
	}
}

void UCRCharacterAttributeComponent::SetDefaults()
{
	CurrentStamina = MaxStamina;
	CurrentWalkSpeed=BaseWalkSpeed;
	CurrentSprintSpeed=BaseSprintSpeed;
}


// Called when the game starts
void UCRCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	SetDefaults();
	
}


// Called every frame
void UCRCharacterAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UseStamina(DeltaTime);
	
}



void UCRCharacterAttributeComponent::UseStamina(float DeltaTime)
{
	if (OwnerMovementComponent->GetIsSprinting())
	{
		CurrentStamina -=StaminaSprintUsedRate*DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f , MaxStamina);
		
	}
	else if (!OwnerMovementComponent->GetIsSprinting())
	{
		CurrentStamina +=StaminaRecoverRate*DeltaTime;
		CurrentStamina = FMath::Clamp(CurrentStamina, 0.0f , MaxStamina);
	}
	if (CurrentStamina<=0)
	{
		bIsStaminaEnd=true;
		if (OnStaminaEndEvent.IsBound())
		{
			OnStaminaEndEvent.Broadcast(true);		

		}
	}
	if (CurrentStamina>=MaxStamina)
	{
		bIsStaminaEnd=false;
		if (OnStaminaEndEvent.IsBound())
		{
			OnStaminaEndEvent.Broadcast(false);	
		}
	}
	
	

	
}

