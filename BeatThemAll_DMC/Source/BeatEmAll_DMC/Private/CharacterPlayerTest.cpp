// Fill out your copyright notice in the Description page of Project Settings.


//#include "CharacterPlayerTest.h"
//#include "Camera/CameraComponent.h"
//#include "Perception/AIPerceptionStimuliSourceComponent.h"
//#include "Perception/AISense_Sight.h"
//
//// Sets default values
//ACharacterPlayerTest::ACharacterPlayerTest()
//{
// 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
//	Camera->SetupAttachment(RootComponent);
//
//	SetUpStimulusSource();
//}
//
//// Called when the game starts or when spawned
//void ACharacterPlayerTest::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ACharacterPlayerTest::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void ACharacterPlayerTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterPlayerTest::MoveForward);
//	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterPlayerTest::MoveRight);
//
//	PlayerInputComponent->BindAxis("TurnCamera", this, &ACharacterPlayerTest::TurnCamera);
//	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterPlayerTest::LookUp);
//}
//
//void ACharacterPlayerTest::MoveForward(float InputValue)
//{
//	FVector ForwardDirection = GetActorForwardVector();
//	AddMovementInput(ForwardDirection, InputValue);
//}
//
//void ACharacterPlayerTest::MoveRight(float InputValue)
//{
//	FVector RightDirection = GetActorRightVector();
//	AddMovementInput(RightDirection, InputValue);
//}
//
//void ACharacterPlayerTest::TurnCamera(float InputValue)
//{
//	AddControllerYawInput(InputValue);
//}
//
//void ACharacterPlayerTest::LookUp(float InputValue)
//{
//	AddControllerPitchInput(InputValue);
//}
//
//void ACharacterPlayerTest::SetUpStimulusSource()
//{
//	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
//	if (StimulusSource)
//	{
//		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
//		StimulusSource->RegisterWithPerceptionSystem();
//	}
//}



