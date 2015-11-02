// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "HelloWorldPrinter.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API AHelloWorldPrinter : public AActor
{
	GENERATED_UCLASS_BODY()

		UPROPERTY()
		int32 myNumber;

	virtual void BeginPlay() override;


};
