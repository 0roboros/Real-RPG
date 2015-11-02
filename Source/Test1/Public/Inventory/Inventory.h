// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InvMatrix.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API AInventory : public AActor
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY()
	AInvMatrix* InvMatr;

	UPROPERTY(BlueprintReadWrite,Category=Inventory)
	TArray<AItem*> Equipment;


	virtual void PostInitializeComponents() override;
	void SpawnInvMatrix();
	void PickUp(AItem* Item);

	UFUNCTION()
	void EquipFirstItem();
};
