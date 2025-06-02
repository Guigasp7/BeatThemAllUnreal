// Fill out your copyright notice in the Description page of Project Settings.


#include "Gruntling.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CollisionQueryParams.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGruntling::AGruntling() :
	Health(50.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseDamage = 2;
	HasHit = false;
	ActionLocked = false;
}

// Called when the game starts or when spawned
void AGruntling::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGruntling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AGruntling::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	Health -= damageAmount;
	if (Health <= 0)
	{		
		Destroy();
	}
	else
	{
		TakingDamage();
	}
	return damageAmount;
}

void AGruntling::TakingDamage()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

	if (animInstance && takingDamageMontage)		
	{
		float const sectionLength = takingDamageMontage->GetSectionLength(1);
		GetCharacterMovement()->DisableMovement();

		animInstance->Montage_Play(takingDamageMontage);

		GetWorldTimerManager().SetTimer(timerStun, this, &AGruntling::ResetMovement, sectionLength);
	}
}

void AGruntling::ResetMovement()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

UAnimMontage* AGruntling::getMontage() const
{
	return attackMontage;
}

int AGruntling::MeleeAttack_Implementation()
{
	if (!ActionLocked)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

		if (animInstance)
		{
			HasHit = false;
			ActionLocked = true;
			animInstance->Montage_Play(attackMontage);
		}
	}
	return 0;
}

UBehaviorTree* AGruntling::GetBehaviorTree() const
{
	return Tree;
}

void AGruntling::AttackCollision()
{
	if (!HasHit)
	{
		USkeletalMeshComponent* GruntlingMesh = GetMesh();
		FVector Start = GruntlingMesh->GetSocketLocation(TEXT("b_MF_Weapon_LSocket"));
		FVector End = GruntlingMesh->GetSocketLocation(TEXT("b_MF_Weapon_LSocket_0"));
		float SphereRadius = 22.f;
		TArray<AActor*> Ignores;
		Ignores.Add(this);
		TArray<FHitResult> HitObjects;
		const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, SphereRadius, UEngineTypes::ConvertToTraceType(ECC_Camera), false, Ignores, EDrawDebugTrace::ForDuration, HitObjects, true, FLinearColor::Red, FLinearColor::Green, 0.3f);

		if (Hit)
		{
			for (FHitResult HitResult : HitObjects)
			{
				AActor* HitActor = HitResult.GetActor();
				if (APlayerCharacter* Player = Cast<APlayerCharacter>(HitActor))
				{
					UGameplayStatics::ApplyDamage(Player, BaseDamage, GetController(), this, defaultDamage);
					HasHit = true;
				}
			}
		}
	}
}

void AGruntling::CanAttackAgain()
{
	ActionLocked = false;
}

