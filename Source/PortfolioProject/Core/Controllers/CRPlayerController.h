// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CRPlayerController.generated.h"

class UCRMovementComponent;
class ACRBaseCharacter;
/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API ACRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void SetPawn(APawn* InPawn) override;

protected:

	virtual void SetupInputComponent() override;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ACRBaseCharacter* CharacterOwner;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UCRMovementComponent* OwnerMovementComponent;

	
	//Movement

	void MoveForward (float Value);
	void MoveRight (float Value);
	void Turn (float Value);
	void LookUp (float Value);
	void StartSprint ();
	void EndSprint ();

	
private:
	
	void Sprint (bool bIsSprinting);
	
	
	
	
};
