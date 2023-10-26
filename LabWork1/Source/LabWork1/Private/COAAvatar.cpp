// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

ACOAAvatar::ACOAAvatar():
RunningSpeed(600.0f),
MaxStamina(100.0f),
Stamina(0.0f),
StaminaGainRate(15.0f),
StaminaDrainRate(60.0f)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;
}

void ACOAAvatar::BeginPlay()
{
	Super::BeginPlay();

	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	bStaminaDrained = false;
}

void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement() -> MovementMode == EMovementMode::MOVE_Walking)
	{
		if (!bRunning || bStaminaDrained)
		{
			Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
			if (Stamina >= MaxStamina)
			{
				bStaminaDrained = false;
				UpdateMovementParams();
			}
		}
		else if (!GetCharacterMovement()->Velocity.IsNearlyZero(0.01f))
		{
			Stamina = FMath::Max(0, Stamina - StaminaDrainRate * DeltaTime);
			if (Stamina == 0)
			{
				bStaminaDrained = true;
				UpdateMovementParams();
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(0, 500.0f, FColor::Purple, FString::Printf(TEXT("Stamina: %f"), Stamina));

	UE_LOG(LogTemp, Warning, TEXT("Stamina : %f"), Stamina);
}

void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ACOAAvatar::RunReleased);

}

void ACOAAvatar::MoveForward(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector ForwardDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, Amount);
}

void ACOAAvatar::MoveRight(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector RightDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightDirection, Amount);
}

void ACOAAvatar::RunPressed()
{
	bRunning = true;
	UpdateMovementParams();
}

void ACOAAvatar::RunReleased()
{
	bRunning = false;
	UpdateMovementParams();
}

void ACOAAvatar::UpdateMovementParams()
{
	GetCharacterMovement()->MaxWalkSpeed =
		bRunning && !bStaminaDrained ? RunningSpeed : WalkingSpeed;
}
