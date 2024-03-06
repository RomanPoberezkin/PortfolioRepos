// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CRBaseCharacter.generated.h"

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

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Compnents")
	UCRMovementComponent* CharacterMovementComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Compnents")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character | Compnents")
	UCameraComponent* CameraComponent;
	

public:	
	
	virtual void Tick(float DeltaTime) override;	


	//Movement methods

	virtual  void MoveForward (float Value);
	virtual  void MoveRight (float Value);
	virtual  void Turn (float Value);
	virtual  void LookUp (float Value);
	virtual  void ChangeSprintCondition (bool bISSprinting);

};
