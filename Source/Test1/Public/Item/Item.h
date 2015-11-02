// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API AItem : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, Category=Item)
	uint8 height;
	UPROPERTY(VisibleAnywhere, Category=Item)
	uint8 length;

	virtual void Init(uint8 h, uint8 l, bool IsActive = 1);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ItemMesh)
	TSubobjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, Category=Item)
	float DefaultBuyPrice;
	UPROPERTY(VisibleAnywhere, Category=Item)
	float DefaultSellPrice;

	UFUNCTION(BlueprintNativeEvent, Category=Equip)
	void OnEquip();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void FlipCollision(bool collide);

public:
	
	uint8 GetHeight();

	uint8 GetLength();

	bool bIsActive;

	void MakeActive();

	UFUNCTION()
	void OnPickedUp();
	
};
