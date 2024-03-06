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
	virtual  void ChangeSprintCondition (bool bISSprinting);

	UFUNCTION(BlueprintCallable)
	UCRCharacterAttributeComponent* GetAttributeComponent () const {return AttributeComponent;}

protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCRMovementComponent* CharacterMovementComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCameraComponent* CameraComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Components")
	UCRCharacterAttributeComponent* AttributeComponent;	
	

private:

	void StaminaEnd (bool StaminaEnd);

};
