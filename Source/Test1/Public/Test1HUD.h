// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "Test1HUD.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ATest1HUD : public AHUD
{
	GENERATED_UCLASS_BODY()

		// Variable for storing the font
		UPROPERTY()
		UFont* HUDFont;
		
		// Primary draw call for the HUD
		virtual void DrawHUD() override;

};
