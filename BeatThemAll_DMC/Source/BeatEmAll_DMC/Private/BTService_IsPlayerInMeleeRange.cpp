// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMeleeRange.h"
#include "EnemyAIController.h"
#include "Gruntling.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Melee Range");
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	auto const* const controller = Cast<AEnemyAIController>(OwnerComponent.GetAIOwner());
	auto const* const gruntling = Cast<AGruntling>(controller->GetPawn());

	auto const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComponent.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), gruntling->GetDistanceTo(player) <= MeleeRange);
}
