// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Powerup.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API APowerup : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Powerup)
	TSubobjectPtr<USphereComponent> TouchSphere;

	UPROPERTY(VisibleDefaultsOnly, Category = Powerup)
	float RotationRate;

	virtual void Tick(float DeltaTime) override;
	
};
