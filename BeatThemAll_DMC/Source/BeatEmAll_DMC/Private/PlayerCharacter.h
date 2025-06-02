// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = Default, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(Category = Default, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	/** Player Maximum Health */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double MaxHealth;

	/** Player Current Health */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double CurrentHealth;

	/** Player Base Damage */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double BaseDamage;

	/** Combo Counter */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ComboCounter;

	/** Is the Player dead */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsDead;

	/** Is the player jumping */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsJumping;

	/** Can the player attack */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ActionLocked;

	/** Is the player attacking */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

	/** Current combo step counter */
	UPROPERTY(Category = Default, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ComboStep;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IMC_Default;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	/** Player wants to attack when true */
	UPROPERTY(BlueprintReadOnly, Category = Default, meta = (AllowPrivateAccess = "true"))
	bool bPressedAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> Attacks;

	/** taking damage animation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DamageAnim;

	/** Death animation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DeathAnim;

	/** after attacks recovery animations */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> Recoveries;

	/** needed for the applydamage to enemy*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> defaultDamage;


public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	/** Called for attack input */
	void Attack(const FInputActionValue& Value);

	/** Trigger attack if Attack button has been pressed and the player can attack */
	void CheckAttackInput();

	UFUNCTION(BlueprintCallable)
	/** Checks the combo step and launches the next attack */
	void LaunchAttack();

	UFUNCTION(BlueprintCallable)
	/** Traces the weapon collision during an attack and damages enemies*/
	void AttackCollision();

	UFUNCTION(BlueprintCallable)
	/** Checks the combo State and play the recovery animation */
	void AttackRecovery();

	UFUNCTION(BlueprintCallable)
	/** Play animation and sound, and locks action on take damage */
	void Damaged();

	UFUNCTION(BlueprintCallable)
	/** Play Animation and sound when player dies, locks controls and pops game over screen */
	void Death();

	/** Checks if dead */
	bool CheckIfDead();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetUpStimulusSource();


public:
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArmComponent; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
