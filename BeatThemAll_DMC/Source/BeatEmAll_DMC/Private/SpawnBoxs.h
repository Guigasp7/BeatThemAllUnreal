// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBoxs.generated.h"

UCLASS()
class ASpawnBoxs : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ASpawnBoxs();

	//will spawn an actor of the selected class
	UFUNCTION(BlueprintCallable)
	bool SpawnActor();

	//Actor class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldSpawn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfEnemiesInAWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfWave;

	//Timing parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AverageSpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when the actor stop playing
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	//Box in which we will spawn the actors

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	FTimerHandle SpawnTimerHandle;

	int CurrentWave;

	UFUNCTION()
	void SpawnActorScheduled();

	//Will schedule an actor spawn
	void ScheduleActorSpawn();

	bool FindValidSpawnLocation(FVector SpawnLocation);
};
