// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ABatteryPickup : public APickup
{
	GENERATED_UCLASS_BODY()

	/** Set the amount of power the battery gives to the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
	float PowerLevel;
	
	/** Overrides the OnPickedUp function (use implementation because this is a blueprintnative event*/
	void OnPickedUp_Implementation() override;
};
