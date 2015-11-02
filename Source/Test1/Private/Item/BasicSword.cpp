// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "BasicSword.h"


ABasicSword::ABasicSword(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Init(4, 2);
}



