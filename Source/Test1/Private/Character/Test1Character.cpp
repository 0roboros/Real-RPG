// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Test1.h"
#include "Test1Character.h"
#include "BatteryPickup.h"
#include "Test1GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "sqlite3.h"
#include "Engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


//////////////////////////////////////////////////////////////////////////
// ATest1Character

ATest1Character::ATest1Character(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Set a base power level for the character
	//Set the dependence of speed on the power level
	SpeedFactor = 0.75f;
	/* UE_LOG(LogTemp, Warning, TEXT("this start:%p"), (void *)this);
	UE_LOG(LogTemp, Warning, TEXT("powerlevel ptr start: %p"), (void *)&PowerLevel);
	UE_LOG(LogTemp, Warning, TEXT("powerlevel start: %f"), PowerLevel);
	UE_LOG(LogTemp, Warning, TEXT("basespeed ptr start: %p"), (void *)&BaseSpeed);
	UE_LOG(LogTemp, Warning, TEXT("basespeed start: %f"), BaseSpeed);*/


	//get stats from sqlite
	//Myself = this;

	//Create our battery collection volume
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}

//////////////////////////////////////////////////////////////////////////
// Input

void ATest1Character::PostInitializeComponents(){
	Super::PostInitializeComponents();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoCollisionFail = true;
	Inv = GetWorld()->SpawnActor<AInventory>(SpawnInfo);
}

int ATest1Character::StaticGetStats(void *me, int columns, char **columnvalues, char **columnnames){
	//UE_LOG(LogTemp, Warning, TEXT("Static me ptr is:%p"), (void *)me);
	
	TArray<FString> UColumnValues;
	TArray<FString> UColumnNames;

	for (int i = 0; i < columns; i++){
		FString fcolumnvalue(columnvalues[i]);
		//UE_LOG(LogTemp, Warning, TEXT("columnvalue is:%s"), *fcolumnvalue);
		UColumnValues.Add(fcolumnvalue);
		FString fcolumnnames(columnnames[i]);
		UColumnNames.Add(fcolumnnames);
	}


	ATest1Character* Myself = static_cast<ATest1Character*>(me);
	if (Myself != NULL)
		if (sizeof(columns) == 4){
		int32 UColumns = columns;
		Myself->GetStats(UColumns, UColumnValues, UColumnNames);
		}
	return 0;
}

void ATest1Character::GetStats(int32 UColumns, TArray<FString> UColumnValues, TArray<FString> UColumnNames){
	if (GEngine){
		//UE_LOG(LogTemp, Warning, TEXT("this after:%p"), (void *)this);
		for (int i = 0; i < UColumns; i++){
			UE_LOG(LogTemp, Warning, TEXT("UColumnValue is %s"), *UColumnValues[i]);
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, UColumnValues[i]);
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT(" = "));
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, UColumnNames[i]);
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Yellow, TEXT("\n"));
			if (UColumnNames[i] == "BasePowerLevel"){
				float pl = FCString::Atof(*UColumnValues[i]);
				PowerLevel = pl;
				//UE_LOG(LogTemp, Warning, TEXT("powerlevel ptr after: %p"), (void *)&PowerLevel);
				//UE_LOG(LogTemp, Warning, TEXT("powerlevel after: %f"), PowerLevel);
			}
			if (UColumnNames[i] == "BaseSpeed"){
				float bs = FCString::Atof(*UColumnValues[i]);
				BaseSpeed = bs;
				//UE_LOG(LogTemp, Warning, TEXT("basespeed ptr after: %p"), (void *)&BaseSpeed);
				//UE_LOG(LogTemp, Warning, TEXT("basespeed after: %f"), BaseSpeed);
			}
			if (UColumnNames[i] == "Health"){
				float hp = FCString::Atof(*UColumnValues[i]);
				Health = hp;
			}
		}
	}
}



void ATest1Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("CollectPickups", IE_Pressed, this, &ATest1Character::PickUp);
	InputComponent->BindAction("EquipFirst", IE_Pressed, this, &ATest1Character::EquipFirst);
	//InputComponent->BindAction("LoadFromDB", IE_Pressed, this, &ATest1Character::LoadFromDB);

	InputComponent->BindAxis("MoveForward", this, &ATest1Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATest1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ATest1Character::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ATest1Character::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ATest1Character::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ATest1Character::TouchStopped);
}


void ATest1Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ATest1Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ATest1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATest1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATest1Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATest1Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATest1Character::PickUp()
{
	float BatteryPower = 0.f;

	ATest1GameMode* MyGameMode = Cast<ATest1GameMode>(UGameplayStatics::GetGameMode(this));

	//if we are currently playing
	if (MyGameMode->GetCurrentState() == ETest1PlayState::EPlaying)
	{
		//Get all overlapping Actors and store them in a CollectedActors array
		TArray<AActor*> CollectedActors;
		CollectionSphere->GetOverlappingActors(CollectedActors);

		//For each Actor collected
		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
		{
			// Cast the collected Actor to ABatteryPickup
			ABatteryPickup* const TestBattery = Cast<ABatteryPickup>(CollectedActors[iCollected]);

			//if the cast is successful, and the battery is valid and active
			if (TestBattery && !TestBattery->IsPendingKill() && TestBattery->bIsActive){
		
				// Store its battter power for adding to the character's power
				BatteryPower = BatteryPower + TestBattery->PowerLevel;
				// Call the battery's OnPickedUp function
				TestBattery->OnPickedUp();
				//Deactivate the battery
				TestBattery->bIsActive = false;
		
			}

			// Cast the collected Actor to AItem

			AItem* Item = Cast<AItem>(CollectedActors[iCollected]);

			if (Item && !Item->IsPendingKill() && Item->bIsActive){
				Inv->PickUp(Item);
			}
		}

		if (BatteryPower > 0.f)
		{
			// Call the blueprinted implementation of PowerUp
			PowerUp(BatteryPower);
		}
	}
}

void ATest1Character::EquipFirst(){
	Inv->EquipFirstItem();
	
}

void ATest1Character::Init(){

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char * sql;

	rc = sqlite3_open("db/pstats.db", &db);
	if (GEngine)
	{
		if (rc == SQLITE_OK){
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Connection Opened!  Yay!"));

			sql = "Select BasePowerLevel, BaseSpeed, Health from player where name = \"player1\"";
			rc = sqlite3_exec(db, sql, ATest1Character::StaticGetStats, this, &zErrMsg);

			if (rc != SQLITE_OK){
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, zErrMsg);
				sqlite3_free(zErrMsg);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Success!\n");
			}

		}
		else{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Connection Failed!  FUCK YOU DAVID!"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, sqlite3_errmsg(db));
		}
	}

	sqlite3_close(db);

	//UE_LOG(LogTemp, Warning, TEXT("PowerLevel ptr done: %p"), (void *)&PowerLevel);
	//UE_LOG(LogTemp, Warning, TEXT("PowerLevel done: %f"), PowerLevel);
	//UE_LOG(LogTemp, Warning, TEXT("basespeed ptr done: %p"), (void *)&BaseSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("basespeed done: %f"), BaseSpeed);

}

void ATest1Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*UE_LOG(LogTemp, Warning, TEXT("Powerlevel Tick: %f"), PowerLevel);
	UE_LOG(LogTemp, Warning, TEXT("PowerLevel ptr Tick: %p"), &PowerLevel);
	UE_LOG(LogTemp, Warning, TEXT("BaseSpeed Tick: %f"), BaseSpeed);
	UE_LOG(LogTemp, Warning, TEXT("BaseSpeed ptr Tick: %p"), &BaseSpeed);*/
	CharacterMovement->MaxWalkSpeed = SpeedFactor * PowerLevel + BaseSpeed;

}
