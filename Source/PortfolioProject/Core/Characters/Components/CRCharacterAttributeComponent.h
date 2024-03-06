// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRCharacterAttributeComponent.generated.h"

class UCRMovementComponent;
class ACRBaseCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStaminaEnd, bool)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTFOLIOPROJECT_API UCRCharacterAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCRCharacterAttributeComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool GetIsStaminaEnd () const {return bIsStaminaEnd;}

	FOnStaminaEnd OnStaminaEndEvent;

	UFUNCTION(BlueprintCallable)
	float GetCurrentStamina () const {return CurrentStamina;}

	//Speed Getters
	
	float GetCurrentWalkSpeed () const {return  CurrentWalkSpeed;}
	float GetCurrentSprintSpeed () const {return  CurrentSprintSpeed;}
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes | Stamina", meta = (ClampMin=0.0, UIMin = 0.0))
	float MaxStamina = 100.0f;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes | Stamina", meta = (ClampMin=0.0, UIMin = 0.0))
	float StaminaSprintUsedRate = 20;
	
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes | Stamina", meta = (ClampMin=0.0, UIMin = 0.0))
	float StaminaRecoverRate = 40;

	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes | Speed", meta = (ClampMin=0.0, UIMin = 0.0))
	float BaseWalkSpeed = 600.0f;
	
	UPROPERTY (EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes | Speed", meta = (ClampMin=0.0, UIMin = 0.0))
	float BaseSprintSpeed = 1000.0f;

	

	

private:

	TWeakObjectPtr<ACRBaseCharacter> CharacterOwner;
	TWeakObjectPtr<UCRMovementComponent> OwnerMovementComponent;
	

	float CurrentStamina;
	float CurrentHealth;

	void SetDefaults ();

	//Stamina

	void UseStamina (float DeltaTime);
	bool bIsStaminaEnd = false;

	//Speed

	float CurrentWalkSpeed;
	float CurrentSprintSpeed;
	
	
	
};
