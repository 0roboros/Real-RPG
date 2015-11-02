// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "PartyMemberFollow.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TEST1_API UPartyMemberFollow : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory) override;
	
};
