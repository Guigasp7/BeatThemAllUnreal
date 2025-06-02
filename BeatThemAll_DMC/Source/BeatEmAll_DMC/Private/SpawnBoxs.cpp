// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnBoxs.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnBoxs::ASpawnBoxs()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setup members;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;

	CurrentWave = 0;
}

// Called when the game starts or when spawned
void ASpawnBoxs::BeginPlay()
{
	Super::BeginPlay();

	//Check if the waves ends
	if (CurrentWave == NumberOfWave)
	{
		bShouldSpawn = false;
	}
	//Schedule first spawn
	if (bShouldSpawn)
	{
		ScheduleActorSpawn();
	}
}

void ASpawnBoxs::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//Remove all timers associated with this object instance
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}



bool ASpawnBoxs::SpawnActor()
{
	bool SpawnedActor = false;
	if (ActorClassToBeSpawned)
	{
		//Calculate the extends of the box
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		//Compute a random position within the box bounds
		FVector SpawnLocation = BoxBounds.Origin;
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();

		if (FindValidSpawnLocation(SpawnLocation))
		{
			//Spawn the actor
			SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;
			if (SpawnedActor)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Actor spawned successfully at location %s"), SpawnLocation.ToString());
				return true;
			}
		}
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor !!!"));
		return false;
	}
	return false;
	//return SpawnedActor;
}

void ASpawnBoxs::ScheduleActorSpawn()
{
	//Compute time offset to spawn
	float DeltaToNextSpawn = AverageSpawnTime + (-RandomSpawnTime + 2 * RandomSpawnTime * FMath::FRand());
	//Schedule spawning
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnBoxs::SpawnActorScheduled, DeltaToNextSpawn, false);
	CurrentWave++;
}

bool ASpawnBoxs::FindValidSpawnLocation(FVector SpawnLocation)
{
	FVector BoxExtent = SpawnBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawnBox->GetComponentLocation();
	//Limited attempt to vavoid infinite loop
	for (int Attempt = 0; Attempt < 1000; ++Attempt)
	{
		//Generate random spawn point within the box
		FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);

		//Check collisions at the spawn point
		FCollisionQueryParams CollisionParams;
		bool bHasCollision = GetWorld()->OverlapBlockingTestByChannel(RandomPoint, FQuat::Identity, ECC_WorldDynamic, FCollisionShape::MakeSphere(30.f), CollisionParams);

		//If no collision is found, it's a valid spawn point
		if (!bHasCollision) 
		{
			return true;
		}
	}
	//If no valid spawn is found after 10 attempt return false
	return false;
}

void ASpawnBoxs::SpawnActorScheduled()
{
	for (int i = 0; i < NumberOfEnemiesInAWave; i++)
	{
		SpawnActor();
	}

	if (CurrentWave == NumberOfWave)
	{
		bShouldSpawn = false;
	}
	else if (bShouldSpawn)
	{
		ScheduleActorSpawn();
	}
}


