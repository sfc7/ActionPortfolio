// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BaseGameplayAbility.h"
#include "PlayerGameplayAbility.generated.h"

class APlayerCharacter;
class APlayerCharacterController;
class UPlayerCombatComponent;
/**
 * 
 */
UCLASS()
class ACTIONPORTFOLIO_API UPlayerGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	APlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	APlayerCharacterController* GetPlayerCharacterControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Character|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

private:	
	TWeakObjectPtr<APlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<APlayerCharacterController> CachedPlayerCharacterController;
};
