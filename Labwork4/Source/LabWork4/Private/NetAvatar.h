// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NetAvatar.generated.h"

/**
 * 
 */
UCLASS()
class ANetAvatar : public ANetBaseCharacter
{
	GENERATED_BODY()
	
public:

	ANetAvatar();

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	UPROPERTY()
	float RunningSpeed;
	
	UPROPERTY()
	float WalkingSpeed;

	UFUNCTION()
	void StartRunning();

	UFUNCTION()
	void StopRunning();

	UPROPERTY()
	bool bIsRunning;

	UFUNCTION(Server, Reliable)
	void ServerStartRunning();

	UFUNCTION(Server, Reliable)
	void ServerStopRunning();

	UFUNCTION()
	void OnRep_IsRunning();

};
