// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CRCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UCRCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category="Character info", meta = (ClampMin=0, UIMin=0))
	float Speed =0.0f;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category="Character info")
	bool bIsInAir;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category="Character info")
	bool bIsTired;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category="Character info")
	bool bIsCrouched;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category="Character info")
	bool bIsProne = false;
	
private:

	TWeakObjectPtr<class ACRBaseCharacter> CharacterOwner;
};
