// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Test1.h"
#include "Test1GameMode.h"
#include "Test1Character.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "Test1HUD.h"

ATest1GameMode::ATest1GameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//set the default HUD class
	HUDClass = ATest1HUD::StaticClass();

	//base decay rate
	DecayRate = 0.05f;

}

void ATest1GameMode::Tick(float DeltaSeconds)
{
	ATest1Character* MyCharacter = Cast<ATest1Character>(UGameplayStatics::GetPlayerPawn(this, 0));

	// if the character still has power
	if (MyCharacter->PowerLevel > 0.05)
	{
		//decrease the character's power
		MyCharacter->PowerLevel = FMath::FInterpTo(MyCharacter->PowerLevel, 0.f, DeltaSeconds, DecayRate);
	}
	else
	{
		SetCurrentState(ETest1PlayState::EGameOver);
	}
}

void ATest1GameMode::SetCurrentState(ETest1PlayState NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void ATest1GameMode::HandleNewState(ETest1PlayState NewState)
{
	switch(NewState)
	{
	// when we're playing, spawnvolumes can spawn
	case ETest1PlayState::EPlaying:
		for (ASpawnVolume* Volume: SpawnVolumeActors)
		{
			Volume->EnableSpawning();
		}
		break;
	// if the game is over, the spawn volumes should deactivate
	case ETest1PlayState::EGameOver:
	{
		for (ASpawnVolume * Volume: SpawnVolumeActors)
		{
			Volume->DisableSpawning();
		}
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		PlayerController->SetCinematicMode(true, true, true);
	}
		break;
	case ETest1PlayState::EUnknown:
	default:
		//do nothing
		break;
	}
}

void ATest1GameMode::BeginPlay()
{
	Super::BeginPlay();

	//find all spawn volume actors

	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.Add(SpawnVolumeActor);
		}
	}

	SetCurrentState(ETest1PlayState::EPlaying);
}