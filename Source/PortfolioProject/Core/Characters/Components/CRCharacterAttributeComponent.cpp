// Fill out your copyright notice in the Description page of Project Settings.


#include "CRCharacterAttributeComponent.h"

#include "CRMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PortfolioProject/Core/Characters/CRBaseCharacter.h"
#include "PortfolioProject/Core/Data/Utils/TraceUtils/TraceUtils.h"


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
	CurrentCrouchSpeed=BaseCrouchSpeed;
	CurrentProneSpeed = BaseProneSpeed;
	UnTiredSpeed=CurrentWalkSpeed;
	
}


bool UCRCharacterAttributeComponent::GetCanSprint()
{
	if (!bIsStaminaEnd&&!bIsCrouched)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UCRCharacterAttributeComponent::GetCanProne()
{
	float ZOffset = CharacterOwner->GetCrouchingCapsuleZOffset();	
	FVector Start = CharacterOwner->GetActorLocation();
	Start.Z-=ZOffset;		
	FVector BoxEtent = FVector( CharacterOwner->GetStandingCapsuleHalfHeight(),CharacterOwner->GetProneCapsuleHalfHeight()*2,  CharacterOwner->GetProneCapsuleHalfHeight() );

	FRotator Rotation = CharacterOwner->GetActorRotation();
	TArray<AActor*> Actors;
	FHitResult HitResult;	
	bool bResult =  UKismetSystemLibrary::BoxTraceSingle(GetWorld(),Start,Start, BoxEtent, Rotation, TraceTypeQuery1, false, Actors, EDrawDebugTrace::None, HitResult, true );
	bIsCanProne=!bResult;
	
	return bIsCanProne;
}

bool UCRCharacterAttributeComponent::GetCanCrouch()
{
	float CapsuleZOffset = 0;
	if (CharacterOwner->GetIsProne())
	{
		CapsuleZOffset=CharacterOwner->GetProneCapsuleZOffset()+20;
	}
	
	FHitResult HitResult;
	FVector Location = CharacterOwner->GetActorLocation();
	Location.Z +=CapsuleZOffset;
	float CapsuleRadius = CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	float CapsuleHalfHeight = CharacterOwner->GetCrouchingCapsuleHalfHeight();
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;
	if (TraceUtils::SweepCapsuleSingleByChannel(GetWorld(), HitResult, Location, Location, CapsuleRadius, CapsuleHalfHeight, FQuat::Identity, ECC_Visibility, QueryParams, ResponseParam, NeedDebug, 1, FColor::Green, FColor::Black))
	{
		bIsCanCrouch=false;
	}
	else
	{
		bIsCanCrouch=true;
	}
	
	return bIsCanCrouch;
}

bool UCRCharacterAttributeComponent::GetCanStand()
{
	float CapsuleZOffset = 0;
	if (CharacterOwner->GetIsCrouching())
	{
		CapsuleZOffset = CharacterOwner->GetCrouchingCapsuleZOffset()+10;
	}
	
	if (CharacterOwner->GetIsProne())
	{
		CapsuleZOffset=CharacterOwner->GetProneCapsuleZOffset()+50;
	}
	
	FHitResult HitResult;
	FVector Location = CharacterOwner->GetActorLocation();
	Location.Z +=CapsuleZOffset;
	float CapsuleRadius = CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
	float CapsuleHalfHeight = CharacterOwner->GetStandingCapsuleHalfHeight();
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	FCollisionResponseParams ResponseParam = FCollisionResponseParams::DefaultResponseParam;
	if (TraceUtils::SweepCapsuleSingleByChannel(GetWorld(), HitResult, Location, Location, CapsuleRadius, CapsuleHalfHeight, FQuat::Identity, ECC_Visibility, QueryParams, ResponseParam, NeedDebug))
	{
		bIsCanStand=false;
	}
	else
	{
		bIsCanStand=true;
	}
	
	return bIsCanStand;
}

bool UCRCharacterAttributeComponent::GetCanJump()
{
	if (!bIsStaminaEnd&&!bIsCrouched&&!bIsProne)
	{
		bIsCanJump=true;
	}
	else
	{
		bIsCanJump=false;
	}
	return bIsCanJump;
}

void UCRCharacterAttributeComponent::SwitchCrouchCondition(bool IsCrouch)
{
	bIsCrouched=IsCrouch;
}

void UCRCharacterAttributeComponent::SwitchProneCondition(bool IsProne)
{
	bIsCrouched=false;
	bIsProne=IsProne;
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
		SwitchTired(true);
	}
	if (CurrentStamina>=MaxStamina)
	{
		bIsStaminaEnd=false;
		if (OnStaminaEndEvent.IsBound())
		{
			OnStaminaEndEvent.Broadcast(false);	
		}
		SwitchTired(false);
	}
	
	

	
}

void UCRCharacterAttributeComponent::SwitchTired(bool IsTired)
{
	bIsTired=IsTired;
	if (IsTired)
	{
		UnTiredSpeed=CurrentWalkSpeed;
		CurrentTiredSpeed=CurrentWalkSpeed*0.5;
		CurrentWalkSpeed=CurrentTiredSpeed;
	}
	else if (!IsTired)
	{
		CurrentWalkSpeed=UnTiredSpeed;
	}

	CharacterOwner->SwitchTired(IsTired , CurrentWalkSpeed);
}

