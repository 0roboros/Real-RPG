// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "BasicBow.h"


ABasicBow::ABasicBow(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Init(2, 4);
}


