// Fill out your copyright notice in the Description page of Project Settings.

#include "Test1.h"
#include "PartyMemberController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "PartyMemberFollow.h"


UPartyMemberFollow::UPartyMemberFollow(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}


EBTNodeResult::Type UPartyMemberFollow::ExecuteTask(class UBehaviorTreeComponent* OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* MyComp = OwnerComp;
	APartyMemberController* MyController = MyComp ? Cast<APartyMemberController>(MyComp->GetOwner()) : NULL;
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	else
	{

		AActor* player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player == NULL){
			UE_LOG(LogTemp, Warning, TEXT("PartyMemberFollow Player is missing! returning Failed!"));
			return EBTNodeResult::Failed;
		}
		float Distance = MyController->GetDistanceTo(player);
		if (Distance < 100.f)
			return EBTNodeResult::Failed;

		FVector Destination = MyController->GetPlayerLocation();
		UBlackboardComponent* MyBlackboard = OwnerComp->GetBlackboardComponent();
		uint8 DestKeyID= MyBlackboard->GetKeyID(TEXT("Destination"));
		UE_LOG(LogTemp, Warning, TEXT("DestKeyID=%d"), DestKeyID);
		MyBlackboard->SetValueAsVector(DestKeyID, Destination);
		return EBTNodeResult::Succeeded;
	}
}