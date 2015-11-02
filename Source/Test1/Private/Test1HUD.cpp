// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "Test1HUD.h"
#include "Test1GameMode.h"
#include "Test1Character.h"
#include "EmptySlot.h"
#include "BasicSword.h"
#include "BasicDagger.h"
#include "BasicBow.h"
#include "BasicLargePotion.h"
#include "BasicSandals.h"
#include "BasicPotion.h"
#include "BasicShield.h"
#include "Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"

ATest1HUD::ATest1HUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Use the RobotoDistanceField font from the engine
	static ConstructorHelpers::FObjectFinder<UFont> HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;
}

void ATest1HUD::DrawHUD()
{
	//Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	//Call to the parent versions of DrawHUD

	Super::DrawHUD();

	//Get the character and print its power level
	ATest1Character* MyCharacter = Cast<ATest1Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	FString PowerLevelString = FString::Printf(TEXT("%PowerLevel: %10.1f"), FMath::Abs(MyCharacter->PowerLevel));
	FString BaseSpeedString = FString::Printf(TEXT("%10.1f"), FMath::Abs(MyCharacter->BaseSpeed));
	FString HealthString = FString::Printf(TEXT("Health: %10.1f"), FMath::Abs(MyCharacter->Health));
	DrawText(PowerLevelString, FColor::White, 50, 50, HUDFont);
	DrawText(HealthString, FColor::White, 300, 50, HUDFont);

	ATest1GameMode* MyGameMode = Cast<ATest1GameMode>(UGameplayStatics::GetGameMode(this));
	//if the game is over

	if (MyGameMode->GetCurrentState() == ETest1PlayState::EGameOver)
	{
		// create a variable for storing the size of printing Game Over
		FVector2D GameOverSize;
		GetTextSize(TEXT("GAME OVER"), GameOverSize.X, GameOverSize.Y, HUDFont);
		DrawText(TEXT("GAME OVER"), FColor::White, (ScreenDimensions.X - GameOverSize.X)/2.0f, (ScreenDimensions.Y - GameOverSize.Y)/2.0f, HUDFont);
	}

	//Draw Inventory Matrix

	
	AInvMatrix* InvMatr = MyCharacter->Inv->InvMatr;
	
	FString EmptySlotSymbol = TEXT("X");
	FString NullSlotSymbol = TEXT("N");
	FString SwordSlotSymbol = TEXT("S");
	FString DaggerSlotSymbol = TEXT("D");
	FString BowSlotSymbol = TEXT("B");
	FString LargePotionSlotSymbol = TEXT("L");
	FString SandalsSlotSymbol = TEXT("A");
	FString PotionSlotSymbol = TEXT("s");
	FString ShieldSlotSymbol = TEXT("H");
	for (uint8 r = 0; r < InvMatr->GetHeight(); r++){
		for (uint8 c = 0; c < InvMatr->GetLength(); c++){
			AItem* slot = InvMatr->Grid[r].Col[c];
			if (slot == NULL)
				DrawText(NullSlotSymbol, FColor::White, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
			else if (Cast<AEmptySlot>(slot) != NULL)
				DrawText(EmptySlotSymbol, FColor::White, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
			else if (Cast<ABasicSword>(slot) != NULL)
				DrawText(SwordSlotSymbol, FColor::Black, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);	
			else if (Cast<ABasicBow>(slot) != NULL)
				DrawText(BowSlotSymbol, FColor::Blue, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
			else if (Cast<ABasicLargePotion>(slot) != NULL)
				DrawText(LargePotionSlotSymbol, FColor::Yellow, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
			else if (Cast<ABasicSandals>(slot) != NULL)
				DrawText(SandalsSlotSymbol, FColor::Red, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
			else if (Cast<ABasicDagger>(slot) != NULL)
				DrawText(DaggerSlotSymbol, FColor::Green, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
			else if (Cast<ABasicPotion>(slot) != NULL)
				DrawText(PotionSlotSymbol, FColor::Green, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
			else if (Cast<ABasicShield>(slot) != NULL)
				DrawText(ShieldSlotSymbol, FColor::Green, 100 + 15 * ((uint32)(c)), 100 + 15 * ((uint32)(r)), HUDFont);
		}
	}

	
	
}

