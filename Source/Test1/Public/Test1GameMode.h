// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "Test1GameMode.generated.h"

// enum to store the current state of gameplay
enum class ETest1PlayState : uint8
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS(minimalapi)
class ATest1GameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Power)
	float DecayRate;

	ETest1PlayState GetCurrentState() const;
	
	void SetCurrentState(ETest1PlayState NewState);

	virtual void BeginPlay() override;

private:


	TArray<class ASpawnVolume*> SpawnVolumeActors;


	ETest1PlayState CurrentState;

	void HandleNewState(ETest1PlayState NewState);
};

FORCEINLINE ETest1PlayState ATest1GameMode::GetCurrentState() const
{
	return CurrentState;
}


