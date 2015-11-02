// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "BasicDagger.h"


ABasicDagger::ABasicDagger(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Init(3, 2);
}


