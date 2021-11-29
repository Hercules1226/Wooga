// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch1.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
AWatch1::AWatch1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	watch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Watch"));
	watch->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AWatch1::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	SetState(EBlinkState::Idle);
}

// Called every frame
void AWatch1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (blinkState)
	{
	case EBlinkState::Idle:
		Idle();
		break;
	case EBlinkState::Blink:
		Blink();
		break;
	case EBlinkState::UnBlink:
		UnBlink();
		break;
	}
	currentTime+= DeltaTime;
	if (player->camLoc)
	{
		//if (currentTime >= 1.f)
		{
			dir = player->camLookAt->GetComponentLocation() - watch->GetComponentLocation();
			dir.Normalize();
			currentTime = 0;
		}
		WatchLookat();

		//SetActorRotation(dir.ToOrientationRotator());

	}

	// ending
	/*
	if (bisEnd == false)
	{
		currentTime += DeltaTime;
		if (currentTime >= 5.f)
		{
			/*watch->SetHiddenInGame(true);

			bisEnd = true;
		}
	}
	*/
}

EBlinkState AWatch1::GetState()
{
	return EBlinkState();
}

void AWatch1::SetState(EBlinkState state)
{
	blinkState = state;
}

void AWatch1::Idle()
{
	if (isBlink == true)
	{
		SetState(EBlinkState::Blink);
	}
}

void AWatch1::Blink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	float amountOnParam = FMath::Lerp(0.0f, 0.5f, playTime);

	watch->SetScalarParameterValueOnMaterials(TEXT("Amount"), amountOnParam * 0.1);


	if (playTime >= 5.0f)
	{
		playTime = 0;

		SetState(EBlinkState::UnBlink);
	}
}

void AWatch1::UnBlink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	float amountOffParam = FMath::Lerp(0.5f,0.0f, playTime);

	watch->SetScalarParameterValueOnMaterials(TEXT("Amount"), amountOffParam * 0.1);

	if (playTime >= 5.0f)
	{
		
		isBlink = false;

		playTime = 0;
		SetState(EBlinkState::Idle);
	}
}

void AWatch1::WatchLookat()
{
	SetActorRotation(dir.ToOrientationRotator());
}

