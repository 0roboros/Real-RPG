// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PartyMember.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API APartyMember : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=BehaviorT)
	class UBehaviorTree* PartyMemberBehaviorT;
};
