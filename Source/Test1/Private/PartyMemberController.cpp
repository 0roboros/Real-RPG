// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "PartyMemberController.h"
#include "PartyMember.h"
#include "Test1Character.h"


APartyMemberController::APartyMemberController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	BehaviorTreeComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComp"));
	bWantsPlayerState = true;
	PrimaryActorTick.bCanEverTick = true;
}

void APartyMemberController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	APartyMember* PartyMember = Cast<APartyMember>(InPawn);

	if (PartyMember && PartyMember->PartyMemberBehaviorT)
	{
		BehaviorTreeComp->StartTree(PartyMember->PartyMemberBehaviorT);
	}

}

void APartyMemberController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

FVector APartyMemberController::GetPlayerLocation()
{
	ATest1Character* player = Cast<ATest1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player != NULL){
		return player->GetActorLocation();
	}
	else{
	UE_LOG(LogTemp, Warning, TEXT("PartyMemberController Player is missing! Returning vector location as 0.f, 0.f, 0.f!"));
	return FVector(0.f,0.f,0.f);
	}
}

float APartyMemberController::GetDistanceTo(AActor* Other)
{
	APawn* MyPawn = GetPawn();
	ATest1Character* player = Cast<ATest1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (MyPawn == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Unable to get Pawn from PartyMemberController, returning 0.f"));
		return 0.f;
	}
	if (player == NULL){
		UE_LOG(LogTemp, Warning, TEXT("Unable to get Player from PartyMemberController, returning 0.f"));
		return 0.f;
	}
	else{
		return MyPawn->GetDistanceTo(Other);
	}
}
