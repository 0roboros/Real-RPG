// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "PartyMemberController.generated.h"


/**
 * 
 */
UCLASS()
class TEST1_API APartyMemberController : public AAIController
{
	GENERATED_UCLASS_BODY()

	
	//TSubobjectPtr<class UBlackboardComponent> BlackboardComp;

	UPROPERTY(VisibleAnywhere, Category=BehaviorT)
	TSubobjectPtr<class UBehaviorTreeComponent> BehaviorTreeComp;

	virtual void Possess(class APawn* InPawn) override;

	virtual void BeginInactiveState() override;

	FVector GetPlayerLocation();

	float GetDistanceTo(AActor* Other);
	//This sets a Blackboard component

	// If there is a line of sight to character, start moving towards him
	//void ChaseTarget();

};
