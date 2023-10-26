// Fill out your copyright notice in the Description page of Project Settings.


#include "COABaseCharacter.h"

// Sets default values
ACOABaseCharacter::ACOABaseCharacter() :
	MaxHealth(100.f),
	HealingRate(10.0f),
	WalkingSpeed(300.0f),	
	Health(0.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACOABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void ACOABaseCharacter::OnConstruction(const FTransform& Transform)
{
	Health = MaxHealth;
	Update = false;
}

// Called every frame
void ACOABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);
}

// Called to bind functionality to input


void ACOABaseCharacter::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

float ACOABaseCharacter::GetHealth()
{
	return Health;
}













