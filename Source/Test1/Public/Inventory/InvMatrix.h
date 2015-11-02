// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "GameFramework/Actor.h"
#include "InvMatrix.generated.h"

/**
 * 
 */

USTRUCT()
struct FRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<class AItem*> Col;

	FRow(){
	}
};

UCLASS()
class TEST1_API AInvMatrix : public AActor
{
	GENERATED_UCLASS_BODY()

	//NOTE: It is UNSAFE to modify the dimensions of Grid

	UPROPERTY()
	TArray<FRow> Grid;

	UPROPERTY()
	uint8 Height;

	UPROPERTY()
	uint8 Length;

	UPROPERTY()
	uint8 BlockDHei;

	UPROPERTY()
	uint8 BlockDLen;

	UPROPERTY()
	uint8 BlockIHei;

	UPROPERTY()
	uint8 BlockILen;

	UPROPERTY()
	uint8 LastRow;

	UPROPERTY()
	uint8 LastCol;

	UFUNCTION()
	void Init(uint8 Hei, uint8 Len);
	
	UFUNCTION()
	AItem* GetNextEmptySlot(uint8 StartRow, uint8 StartCol);

	UFUNCTION()
	uint8 CheckEnoughSpace(uint8 Hei, uint8 Len, uint8 ItemHeight, uint8 ItemLength);

	UFUNCTION()
	AItem* TakeFirstItem();

	UFUNCTION()
	AItem* TakeItem(uint8 Ro, uint8 Co);

public:

	UFUNCTION()
	uint8 GetHeight();
	
	UFUNCTION()
	uint8 GetLength();

	UFUNCTION()
	void PickUp(AItem* Item);
};

