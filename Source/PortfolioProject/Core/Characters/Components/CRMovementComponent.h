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
	
	float GetCurrentMaxWalkSpeed () const {return MaxWalkSpeed;}
	bool GetIsSprinting () const {return bIsSprintingCondition;}

	void ChangeSprintCondition (bool bIsSprinting=false);
	

	
protected:

	//Delta for adding speed while sprinting
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Settings | Speed", meta = (ClampMin = 0.0f, UIMin =0.0f))
	float SprintSpeedDelta = 300.0f;

private:

	bool bIsSprintingCondition = false;
	
};
