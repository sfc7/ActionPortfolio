// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Player/PlayerCharacterAnimInstance.h"
#include "Character/PlayerCharacter.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter) {
		OwningPlayerCharacter = Cast<APlayerCharacter>(OwningCharacter);
	}
}

void UPlayerCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration) {
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else {
		IdleElpasedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreshold);
	}
}
