// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CRBaseCharacter.generated.h"

class UCRCharacterAttributeComponent;
class UCameraComponent;
class USpringArmComponent;
class UCRMovementComponent;

UCLASS()
class PORTFOLIOPROJECT_API ACRBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ACRBaseCharacter(const FObjectInitializer& ObjectInitializer);

	UCRMovementComponent* GetCharacterMovementComponent () const ;



	//Movement methods

	virtual  void MoveForward (float Value);
	virtual  void MoveRight (float Value);
	virtual  void Turn (float Value);
	virtual  void LookUp (float Value);
	virtual void Jump() override;
	virtual void StartSprint ();
	virtual void EndSprint ();
	virtual void SwitchTired (bool bISTired, float NewWalkSpeed);
	virtual void StandToCrouch ();
	virtual void CrouchToStand ();
	virtual void CrouchToProne ();
	virtual void ProneToCrouch ();
	virtual void ProneToStand ();
	

	//Components getters

	float GetStandingCapsuleHalfHeight () const {return StandingCapsuleHalfHeight;}
	float GetCrouchingCapsuleHalfHeight () const {return CrouchCapsuleHalfHeight;}
	float GetCrouchingCapsuleZOffset () const {return CrouchingCapsuleHalfHeightOffset;}
	float GetProneCapsuleZOffset () const {return ProneCapsuleHalfHeightOffset;}



	//Conditions

	bool GetIsCrouching () const {return bIsCrouching;}
	bool GetIsProne () const {return bIsProne;}
	
	UFUNCTION(BlueprintCallable)
	UCRCharacterAttributeComponent* GetAttributeComponent () const {return AttributeComponent;}

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SetCharacterDefaults();

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCRMovementComponent* CharacterMovementComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Components | SpringArm")
	float SpringArmZOffset = 30;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCameraComponent* CameraComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCRCharacterAttributeComponent* AttributeComponent;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Components | Capsule")
	float CrouchCapsuleHalfHeight = 40.0f;
	
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Components | Capsule")
	float ProneCapsuleHalfHeight = 20.0f;

	

private:

	void StaminaEnd (bool StaminaEnd);

	bool bIsCrouching = false;
	bool bIsProne = false;

	//Components

	float StandingCapsuleHalfHeight;
	float CrouchingCapsuleHalfHeightOffset;
	float CrouchingSpringArmZOffset;

	float ProneCapsuleHalfHeightOffset;
	float ProneSpringArmZOffset;


	

};
