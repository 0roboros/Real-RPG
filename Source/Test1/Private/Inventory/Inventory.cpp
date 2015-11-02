// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "BasicSword.h"
#include "BasicBow.h"
#include "BasicLargePotion.h"
#include "BasicSandals.h"
#include "BasicDagger.h"
#include "BasicPotion.h"
#include "Inventory.h"


AInventory::AInventory(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	/*InvMatr = PCIP.CreateDefaultSubobject<AInvMatrix>(this, TEXT("InvMatrix"));*/

}

void AInventory::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpawnInvMatrix();
}

void AInventory::SpawnInvMatrix(){

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoCollisionFail = true;
	InvMatr = GetWorld()->SpawnActor<AInvMatrix>(SpawnInfo);
	InvMatr->Init(15, 15);
	
	/*AItem* Excalibur = GetWorld()->SpawnActor<ABasicSword>(SpawnInfo);
	AItem* Daedalus = GetWorld()->SpawnActor<ABasicBow>(SpawnInfo);
	AItem* Butterfly = GetWorld()->SpawnActor<ABasicDagger>(SpawnInfo);
	AItem* Bottle = GetWorld()->SpawnActor<ABasicLargePotion>(SpawnInfo);
	AItem* BootsofTravel = GetWorld()->SpawnActor<ABasicSandals>(SpawnInfo);
	
	InvMatr->PickUp(Excalibur);
	InvMatr->PickUp(Daedalus);
	InvMatr->PickUp(Butterfly);
	InvMatr->PickUp(Bottle);
	InvMatr->PickUp(BootsofTravel);*/

	/*for (int i = 0; i < 5; i++){
		AItem* Salve = GetWorld()->SpawnActor<ABasicPotion>(SpawnInfo);
		InvMatr->PickUp(Salve);
	}*/
}

void AInventory::PickUp(AItem* Item){
	InvMatr->PickUp(Item);
}

void AInventory::EquipFirstItem(){

		AItem* Equip = InvMatr->TakeFirstItem();
		Equipment.Add(Equip);
		Equip->OnEquip();
	
}
