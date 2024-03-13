// Fill out your copyright notice in the Description page of Project Settings.


#include "CRBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CRCharacterAttributeComponent.h"
#include "Components/CRMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACRBaseCharacter::ACRBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super (ObjectInitializer.SetDefaultSubobjectClass<UCRMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	CharacterMovementComponent = Cast<UCRMovementComponent>(GetCharacterMovement());
	
	AttributeComponent=CreateDefaultSubobject<UCRCharacterAttributeComponent>(TEXT("CharacterAttributes"));

	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT ("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	FVector SpringArmOffset = SpringArmComponent->TargetOffset;
	SpringArmOffset.Z +=SpringArmZOffset;
	SpringArmComponent->TargetOffset=SpringArmOffset;	
	SpringArmComponent->bUsePawnControlRotation= true;
	
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT ("Follow Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent -> bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = 1;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	

	SetCharacterDefaults();
}

void ACRBaseCharacter::SetCharacterDefaults()
{
	StandingCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	CrouchingCapsuleHalfHeightOffset = (StandingCapsuleHalfHeight-CrouchCapsuleHalfHeight)*0.5;
	CrouchingSpringArmZOffset = CrouchingCapsuleHalfHeightOffset;

	ProneCapsuleHalfHeightOffset = (CrouchCapsuleHalfHeight-ProneCapsuleHalfHeight)*0.5;
	ProneSpringArmZOffset=ProneCapsuleHalfHeightOffset;
}

UCRMovementComponent* ACRBaseCharacter::GetCharacterMovementComponent() const
{
	UCRMovementComponent* Movement = Cast<UCRMovementComponent>(GetCharacterMovement());
	return  Movement;
}

// Called when the game starts or when spawned
void ACRBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AttributeComponent)
	{
		AttributeComponent->OnStaminaEndEvent.AddUObject(this, &ACRBaseCharacter::StaminaEnd);
		CharacterMovementComponent->SetDefaultMaxWalkSpeed(AttributeComponent->GetCurrentWalkSpeed());
	}
	
	
}

// Called every frame
void ACRBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ACRBaseCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		//Реализация поворота персонажа за камерой ТОЛЬКО во время движения
		FRotator YawRotator (0.0f , GetControlRotation().Yaw, 0.0f);
		FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector);		
		AddMovementInput(ForwardVector, Value);	
	}
}

void ACRBaseCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		//Реализация поворота персонажа за камерой ТОЛЬКО во время движения
		FRotator YawRotator (0.0f , GetControlRotation().Yaw, 0.0f);
		FVector RightVector = YawRotator.RotateVector(FVector::RightVector);
		
		AddMovementInput(RightVector, Value);
	}
}

void ACRBaseCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ACRBaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ACRBaseCharacter::Jump()
{
	if (AttributeComponent->GetCanJump())
	{
		Super::Jump();
	}
}

void ACRBaseCharacter::StartSprint()
{
	if (!AttributeComponent->GetIsStaminaEnd() && AttributeComponent->GetCanSprint())
	{		
		float NewSpeed = AttributeComponent->GetCurrentSprintSpeed();
		GetCharacterMovementComponent()->ChangeSprintCondition(true, NewSpeed);
	}
	
}

void ACRBaseCharacter::EndSprint()
{
	float NewSpeed = AttributeComponent->GetCurrentWalkSpeed();
	GetCharacterMovementComponent()->ChangeSprintCondition(false, NewSpeed);
}



void ACRBaseCharacter::SwitchTired(bool bISTired, float NewWalkSpeed)
{
	GetCharacterMovementComponent()->ChangeTiredCondition(bISTired, NewWalkSpeed);
}

void ACRBaseCharacter::StandToCrouch()
{
	if (AttributeComponent->GetCanCrouch())
	{
		AttributeComponent->SwitchCrouchCondition(true);
		float NewWalkSpeed = AttributeComponent->GetCurrentCrouchSpeed();
		CharacterMovementComponent->StartCrouching(NewWalkSpeed);

		UCapsuleComponent* CurrentCapsuleComponent = GetCapsuleComponent();
		CurrentCapsuleComponent->SetCapsuleHalfHeight(CrouchCapsuleHalfHeight);
		
		USkeletalMeshComponent* CurrentSkeletalMeshComponent = GetMesh();
		FVector SkeletRelativeLocation =  CurrentSkeletalMeshComponent->GetRelativeLocation();
		SkeletRelativeLocation.Z +=CrouchingCapsuleHalfHeightOffset;
		CurrentSkeletalMeshComponent->SetRelativeLocation(SkeletRelativeLocation);

		FVector SpringArmOffset = SpringArmComponent->TargetOffset;
		SpringArmOffset.Z -=CrouchingSpringArmZOffset;
		SpringArmComponent->TargetOffset=SpringArmOffset;
				
		bIsCrouching=true;

	}
}

void ACRBaseCharacter::CrouchToStand()
{
	if (AttributeComponent->GetCanStand())
	{
		AttributeComponent->SwitchCrouchCondition(false);
		float NewWalkSpeed = AttributeComponent->GetCurrentWalkSpeed();
		CharacterMovementComponent->EndCrouching(NewWalkSpeed);
		
		UCapsuleComponent* CurrentCapsuleComponent = GetCapsuleComponent();
		CurrentCapsuleComponent->SetCapsuleHalfHeight(StandingCapsuleHalfHeight);
		
		USkeletalMeshComponent* CurrentSkeletalMeshComponent = GetMesh();
		FVector SkeletRelativeLocation =  CurrentSkeletalMeshComponent->GetRelativeLocation();
		SkeletRelativeLocation.Z -=CrouchingCapsuleHalfHeightOffset;
		CurrentSkeletalMeshComponent->SetRelativeLocation(SkeletRelativeLocation);
		
		FVector SpringArmOffset = SpringArmComponent->TargetOffset;
		SpringArmOffset.Z +=CrouchingSpringArmZOffset;
		SpringArmComponent->TargetOffset=SpringArmOffset;

		bIsCrouching = false;

	}
}

void ACRBaseCharacter::CrouchToProne()
{
	if (AttributeComponent->GetCanProne())
	{
		AttributeComponent->SwitchProneCondition(true);
		float NewWalkSpeed = AttributeComponent->GetCurrentProneSpeed();
		CharacterMovementComponent->StartProne(NewWalkSpeed);
		
		UCapsuleComponent* CurrentCapsuleComponent = GetCapsuleComponent();
		CurrentCapsuleComponent->SetCapsuleHalfHeight(ProneCapsuleHalfHeight);
		
		bIsCrouching=false;
		bIsProne = true;

	}
}

void ACRBaseCharacter::ProneToCrouch()
{
	if (AttributeComponent->GetCanCrouch())
	{
		AttributeComponent->SwitchProneCondition(false);
		AttributeComponent->SwitchCrouchCondition(true);
		float NewWalkSpeed = AttributeComponent->GetCurrentCrouchSpeed();
		CharacterMovementComponent->EndProne(AttributeComponent->GetCurrentWalkSpeed());
		CharacterMovementComponent->StartCrouching(NewWalkSpeed);

		UCapsuleComponent* CurrentCapsuleComponent = GetCapsuleComponent();
		CurrentCapsuleComponent->SetCapsuleHalfHeight(CrouchCapsuleHalfHeight);
		
		// USkeletalMeshComponent* CurrentSkeletalMeshComponent = GetMesh();
		// FVector SkeletRelativeLocation =  CurrentSkeletalMeshComponent->GetRelativeLocation();
		// SkeletRelativeLocation.Z +=(ProneCapsuleHalfHeightOffset*0.5);
		// CurrentSkeletalMeshComponent->SetRelativeLocation(SkeletRelativeLocation);		
		
		bIsCrouching=true;
		bIsProne = false;
	}
}

void ACRBaseCharacter::ProneToStand()
{
	if (AttributeComponent->GetCanStand())
	{
		AttributeComponent->SwitchProneCondition(false);
		float NewWalkSpeed = AttributeComponent->GetCurrentWalkSpeed();
		CharacterMovementComponent->EndProne(NewWalkSpeed);
		
		UCapsuleComponent* CurrentCapsuleComponent = GetCapsuleComponent();
		CurrentCapsuleComponent->SetCapsuleHalfHeight(StandingCapsuleHalfHeight);
		
		USkeletalMeshComponent* CurrentSkeletalMeshComponent = GetMesh();
		FVector SkeletRelativeLocation =  CurrentSkeletalMeshComponent->GetRelativeLocation();
		SkeletRelativeLocation.Z -=(ProneCapsuleHalfHeightOffset+10);//+CrouchingCapsuleHalfHeightOffset+10.0);
		CurrentSkeletalMeshComponent->SetRelativeLocation(SkeletRelativeLocation);
		
		FVector SpringArmOffset = SpringArmComponent->TargetOffset;
		SpringArmOffset.Z +=CrouchingSpringArmZOffset;
		SpringArmComponent->TargetOffset=SpringArmOffset;
		
		bIsProne = false;
	}
	else if (AttributeComponent->GetCanCrouch())
	{
		ProneToCrouch();
	}
	else
	{		
		return;
	}
}

void ACRBaseCharacter::StaminaEnd(bool StaminaEnd)
{
	if (StaminaEnd)
	{
		EndSprint();
	}
}

