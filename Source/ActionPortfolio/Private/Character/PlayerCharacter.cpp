// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "Component/Input/CharacterInputComponent.h"
#include "CharacterGamePlayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset/StartUpData/DataAsset_CharacterStartUpData.h"
#include "Component/Combat/PlayerCombatComponent.h"
#include "DebugHelper.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	 
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);	
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 이미 유효한 데이터 에셋을 할당했는지 확인
	if (!CharacterStartUpData.IsNull()) {
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous()) {
			LoadedData->GiveToAbilitySystemComponent(BaseAbilitySystemComponent); // 가상함수니까 Subclassof 밑에 클래스의 GiveToAbilitySystemComponent 다 실행
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigData, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigData->DefaultMappingContext, 0);

	UCharacterInputComponent* CharacterInputComponent = CastChecked<UCharacterInputComponent>(PlayerInputComponent);

	CharacterInputComponent->BindNativeInputAction(InputConfigData, CharacterGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	CharacterInputComponent->BindNativeInputAction(InputConfigData, CharacterGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	CharacterInputComponent->BindAbilityInputAction(InputConfigData,this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void APlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f) {
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
		
	if (MovementVector.X != 0.f) {
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f) {
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f) {
		AddControllerYawInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void APlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
