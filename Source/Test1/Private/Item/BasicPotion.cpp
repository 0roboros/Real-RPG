// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "BasicPotion.h"


ABasicPotion::ABasicPotion(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Init(1, 1);
}


