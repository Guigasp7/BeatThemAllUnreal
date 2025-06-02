#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "Gruntling.generated.h"

UCLASS()
class AGruntling : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGruntling();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float damageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	void TakingDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* takingDamageMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* attackMontage;

	UAnimMontage* getMontage() const;

	UFUNCTION(BlueprintCallable)
	int MeleeAttack_Implementation();


	UBehaviorTree* GetBehaviorTree() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool HasHit;

	/** Can the player attack */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ActionLocked;

	UFUNCTION(BlueprintCallable)
	void AttackCollision();

	UFUNCTION(BlueprintCallable)
	void CanAttackAgain();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> defaultDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* Tree;

private:
	FTimerHandle timerStun;

	void ResetMovement();

};


