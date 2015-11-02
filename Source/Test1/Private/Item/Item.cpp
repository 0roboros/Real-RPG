// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "Item.h"


AItem::AItem(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ItemMesh"));
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
	Mesh->WakeRigidBody();
}

void AItem::Init(uint8 h, uint8 l, bool IsActive){
	height = h;
	length = l;
	bIsActive = IsActive;
}

void AItem::MakeActive(){
	bIsActive = 1;
	Mesh->SetHiddenInGame(false);
	Mesh->SetSimulatePhysics(true);
	Mesh->WakeRigidBody();
}

uint8 AItem::GetHeight(){
	return height;
}

uint8 AItem::GetLength(){
	return length;
}

void AItem::OnPickedUp()
{
	if (bIsActive == 1)
		return;
	if (Mesh)
	{
		Mesh->SetSimulatePhysics(false);
		//Mesh->SetCollisionObjectType(ECC_WorldDynamic);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		Mesh->SetHiddenInGame(true);
		bIsActive = 0;
	}
}

void AItem::OnEquip_Implementation()
{
	Mesh->SetHiddenInGame(false);
}

void AItem::FlipCollision(bool Collide){
	if (Collide){
		//Mesh->SetSimulatePhysics(true);
		//Mesh->SetCollisionObjectType(ECC_MAX);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	}
	else{
		//Mesh->SetSimulatePhysics(false);
		//Mesh->SetCollisionObjectType(ECC_WorldDynamic);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	}
}
