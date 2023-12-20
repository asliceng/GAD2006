// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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


	UFUNCTION()
	void StartRunning();

	UFUNCTION()
	void StopRunning();

	UPROPERTY()
	float RunningSpeed;

	UPROPERTY()
	float WalkingSpeed;

	UFUNCTION(Server, Reliable)
	void ServerStartRunning();

	UFUNCTION(Server, Reliable)
	void ServerStopRunning();

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_IsRunning)
	bool bIsRunning;

	UFUNCTION()
	void OnRep_IsRunning();

};
