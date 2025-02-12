// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/PlayerGameplayAbility.h"
#include "Controller/PlayerCharacterController.h"
#include "Character/PlayerCharacter.h"

APlayerCharacter* UPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
    if (!CachedPlayerCharacter.IsValid()) {
        CachedPlayerCharacter = Cast<APlayerCharacter>(CurrentActorInfo->AvatarActor);
    }
    
    return CachedPlayerCharacter.IsValid()? CachedPlayerCharacter.Get() : nullptr;
}

APlayerCharacterController* UPlayerGameplayAbility::GetPlayerCharacterControllerFromActorInfo()
{
    if (!CachedPlayerCharacterController.IsValid()) {
        CachedPlayerCharacterController = Cast<APlayerCharacterController>(CurrentActorInfo->PlayerController);
    }

    return CachedPlayerCharacterController.IsValid()? CachedPlayerCharacterController.Get() : nullptr;
}

UPlayerCombatComponent* UPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
    return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
