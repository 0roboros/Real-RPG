// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "BasicLargePotion.h"


ABasicLargePotion::ABasicLargePotion(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Init(2, 1);
}


