// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"
#include "CombatInterface.h"
#include "EnemyAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	auto const OutOfRange = !OwnerComponent.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	auto const * const controller = OwnerComponent.GetAIOwner();
	auto* const gruntling = Cast<AGruntling>(controller->GetPawn());

	//if the gruntling supports the ICombatInterface, cast and call the execute_MeleeAttack function
	if (auto* const icombat = Cast<ICombatInterface>(gruntling))
	{
		//check to see if the montage has finished so we don't play it again
		if (MontageHasFinished(gruntling))
		{
			icombat->Execute_MeleeAttack(gruntling);
		}
	}

	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_MeleeAttack::MontageHasFinished(AGruntling* const gruntling)
{
	return gruntling->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(gruntling->getMontage());
}
