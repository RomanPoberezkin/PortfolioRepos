// Fill out your copyright notice in the Description page of Project Settings.


#include "CRBaseCharacter.h"
#include "Camera/CameraComponent.h"
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
	SpringArmComponent->bUsePawnControlRotation= true;
	
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT ("Follow Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent -> bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = 1;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	

	
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
	Super::Jump();
}

void ACRBaseCharacter::StartSprint()
{
	if (!AttributeComponent->GetIsStaminaEnd())
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

void ACRBaseCharacter::ChangeSprintCondition(bool bISSprinting)
{

	
		
}

void ACRBaseCharacter::StaminaEnd(bool StaminaEnd)
{
	if (StaminaEnd)
	{
		EndSprint();
	}
}

