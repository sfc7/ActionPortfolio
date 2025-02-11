// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class ABaseWeapon;
/**
 * 
 */
UCLASS()
class ACTIONPORTFOLIO_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ABaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	ABaseWeapon* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Character|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Character|Combat")
	ABaseWeapon* GetCharacterCurrentEquippedWeapon() const;

private:
	TMap<FGameplayTag, ABaseWeapon*> CharacterCarriedWeaponMap;
	
};
