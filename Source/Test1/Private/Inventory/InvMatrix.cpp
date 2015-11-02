// Fill out your copyright notice in the Description page of Project Settings.


#include "Test1.h"
#include "InvMatrix.h"
#include "EmptySlot.h"



AInvMatrix::AInvMatrix(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

void AInvMatrix::Init(uint8 Hei, uint8 Len)
{
	Height = Hei;
	Length = Len;
	
	for (uint8 r = 0; r < Height; r++){
		FRow ArrayRow;
		for (uint8 c = 0; c < Length; c++){
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.bNoCollisionFail = true;
			AItem* coordinate = GetWorld()->SpawnActor<AEmptySlot>(SpawnInfo);
			ArrayRow.Col.Add(coordinate);
		}
		Grid.Add(ArrayRow);
	}
	
}

void AInvMatrix::PickUp(AItem* Item)
{
	LastRow = 0;
	LastCol = 0;
	uint8 ItemHeight = Item->GetHeight();
	uint8 ItemLength = Item->GetLength();
	UE_LOG(LogTemp, Warning, TEXT("Height:%d"), ItemHeight);
	UE_LOG(LogTemp, Warning, TEXT("Length:%d"), ItemLength);

	while (GetNextEmptySlot(LastRow, LastCol) != NULL){
		uint8 state = CheckEnoughSpace(LastRow, LastCol, ItemHeight, ItemLength);
		if (state == 0){
			UE_LOG(LogTemp, Warning, TEXT("State 0"));
			UE_LOG(LogTemp, Warning, TEXT("LastRow:%d"), LastRow);
			UE_LOG(LogTemp, Warning, TEXT("LastCol:%d"), LastCol);
			for (uint8 r = LastRow; r < LastRow + ItemHeight; r++){
				for (uint8 c = LastCol; c < LastCol + ItemLength; c++){
					AItem* slot = Grid[r].Col[c];

					if ((!slot) || (!slot->IsValidLowLevel()))
					{ 
						slot->ConditionalBeginDestroy();
					}
				
					Grid[r].Col[c] = Item;
					Item->bIsActive = 0;
					Item->OnPickedUp();
				}
			}
			
			break;
		}
		else if (state == 1){
			LastCol = BlockDLen + BlockILen - 1;
		}
		else if (state == 2){
			LastCol = 0;
			LastRow++;
		}
		if (LastRow >= Height)
			return;
	}

	
}

AItem* AInvMatrix::GetNextEmptySlot(uint8 StartRow = 0, uint8 StartCol = 0)
{
	
	for (StartRow;  StartRow < Height; StartRow++){
		for (StartCol; StartCol < Length; StartCol++){
			if (Cast<AEmptySlot>(Grid[StartRow].Col[StartCol]) != NULL){
				LastRow = StartRow;
				LastCol = StartCol;
				return Grid[StartRow].Col[StartCol];
			}		
		}
		StartCol = 0;
	}
	
	
	return NULL;
}

uint8 AInvMatrix::CheckEnoughSpace(uint8 Hei, uint8 Len, uint8 ItemHeight, uint8 ItemLength)
{
	
	if (((Hei + ItemHeight) > Height) || ((Len + ItemLength) > Length))
	return 2;
	for (uint8 r = Hei; r < Hei + ItemHeight; r++){
		for (uint8 c = Len; c < Len + ItemLength; c++){
			if (Cast<AEmptySlot>(Grid[r].Col[c]) == NULL){
				BlockDHei = r;
				BlockDLen = c;
				BlockILen = Grid[r].Col[c]->GetLength();
				return 1;
			}
		}
	}
	
	return 0;
}
AItem* AInvMatrix::TakeFirstItem(){	
	return TakeItem(0, 0);
}

AItem* AInvMatrix::TakeItem(uint8 Ro, uint8 Co){

	AItem* Item = Grid[Ro].Col[Co];
	while (Ro > 0){
		Ro--;
		if (Grid[Ro].Col[Co] != Item){
			Ro++;
			break;
		}		
	}

	while (Co > 0){
		Co--;
		if (Grid[Ro].Col[Co] != Item){
			Co++;
			break;
		}

	}

	for (uint8 r = Ro; r < Ro + Item->GetHeight(); r++){
		for (uint8 c = Co; c < Co + Item->GetLength(); c++){
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.bNoCollisionFail = true;
			AItem* coordinate = GetWorld()->SpawnActor<AEmptySlot>(SpawnInfo);
			Grid[r].Col[c] = coordinate;
		}
	}

	return Item;
}

uint8 AInvMatrix::GetHeight(){
	return Height;
}

uint8 AInvMatrix::GetLength(){
	return Length;
}


