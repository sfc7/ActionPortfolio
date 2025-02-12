// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "CharacterInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONPORTFOLIO_API UCharacterInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleaseFunc);

};
template<class UserObject, typename CallbackFunc>
inline void UCharacterInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	if (UInputAction* FoundAction = InputConfig->FindNativeInputActionByTag(InputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UCharacterInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleaseFunc)
{
	checkf(InputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	for (const FCharacterInputConfig& AbilityInputActionConfig : InputConfig->AbilityInputActions) {
		if (!AbilityInputActionConfig.IsValid()) continue;

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleaseFunc, AbilityInputActionConfig.InputTag);
	}
}
 