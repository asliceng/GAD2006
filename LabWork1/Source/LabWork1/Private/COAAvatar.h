// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "COABaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "COAAvatar.generated.h"


/**
 * 
 */
UCLASS()
class ACOAAvatar : public ACOABaseCharacter
{
	GENERATED_BODY()


public:
	ACOAAvatar();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "COA")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "COA")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float StaminaGainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	bool bStaminaDrained;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	bool bRunning;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void RunPressed();
	void RunReleased();

	void UpdateMovementParams();
	
};
