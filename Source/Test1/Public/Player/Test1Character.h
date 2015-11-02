// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Inventory.h"
#include "Test1Character.generated.h"

UCLASS(config=Game)
class ATest1Character : public ACharacter
{
	GENERATED_UCLASS_BODY()

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Myself)
	//ATest1Character * Myself;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

	/** Collection Volume */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Power)
	TSubobjectPtr<class USphereComponent> CollectionSphere;

	/** Power level of our character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Power)
	float PowerLevel;

	/** Power multiplier for the speed of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Power)
	float SpeedFactor;

	/** Baseline speed of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Power)
	float BaseSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
	float Health;

	/** Character's Inventory*/
	UPROPERTY(BlueprintReadWrite, Category=Inventory)
	AInventory* Inv;
	

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

public:

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category=GetStats)
	void Init();

	UFUNCTION(BlueprintCallable, Category=GetStats)
	void GetStats(int32 UColumns, TArray<FString> UColumnValues, TArray<FString> UColumnNames);

protected:

	static int StaticGetStats(void*, int, char**, char**);

	void PostInitializeComponents() override;

	/** Called when we press a key, to collect any batteries inside the SphereComponent */
	UFUNCTION(BlueprintCallable, Category=Power)
	void PickUp();

	UFUNCTION(BlueprintCallable, Category = Power)
	void EquipFirst();

	/** Called by CollectBatteries() to use the Blueprinted PowerUp functionality  */
	UFUNCTION(BlueprintImplementableEvent, Category=Power)
	void PowerUp(float BatteryPower);

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};

