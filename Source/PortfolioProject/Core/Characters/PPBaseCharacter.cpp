// Fill out your copyright notice in the Description page of Project Settings.


#include "PPBaseCharacter.h"

// Sets default values
APPBaseCharacter::APPBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

