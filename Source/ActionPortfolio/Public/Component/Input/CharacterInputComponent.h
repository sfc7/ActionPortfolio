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
 