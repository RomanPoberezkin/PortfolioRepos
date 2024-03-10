// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CRMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UCRMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	virtual float GetMaxSpeed() const override;
	
	float GetCurrentMaxWalkSpeed () const {return MaxWalkSpeed;}
	bool GetIsSprinting () const {return bIsSprinting;}

	void ChangeSprintCondition (bool IsSprinting=false, float NewSpeed=0.0f);
	void SetDefaultMaxWalkSpeed (float NewSpeed);

	void ChangeTiredCondition (bool IsTired, float NewWalkSpeed);

	void StartCrouching (float NewWalkSpeed);
	void EndCrouching (float NewWalkSpeed);

	void StartProne (float NewWalkSpeed);
	void EndProne (float NewWalkSpeed);



	
protected:

	//Delta for adding speed while sprinting
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Settings | Speed", meta = (ClampMin = 0.0f, UIMin =0.0f))
	float SprintSpeedDelta = 300.0f;

private:

	bool bIsSprinting = false;
	bool bIsCrouching = false;
	bool bIsWalking = true;
	bool bIsTired = false;
	bool bIsProne = false;

	//Speed
	float BaseWalkSpeed;
	float CurrentSprintSpeed;
	float CurrentCrouchingSpeed;
	float CurrentProneSpeed;
	float CurrentWalkingSpeed;
	float CurrentTiredSpeed;




	
};
