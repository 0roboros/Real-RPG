// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "BasicShield.h"


ABasicShield::ABasicShield(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Init(3, 3);
}


