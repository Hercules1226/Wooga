// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch1.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "Components/StaticMeshComponent.h"
#include "IconSpot.h"
#include "Icon1.h"
#include "SJ_Actor_KnowledgePoint.h"
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
	spot = Cast<AIconSpot>(UGameplayStatics::GetActorOfClass(GetWorld(), AIconSpot::StaticClass()));
	icon1 = Cast<AIcon1>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon1::StaticClass()));
	pointMachine = Cast<ASJ_Actor_KnowledgePoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_KnowledgePoint::StaticClass()));
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
	if (player->camLoc)
	{
		dir = player->camLookAt->GetComponentLocation() - GetActorLocation();
		dir.Normalize();
		targetrot = dir.ToOrientationRotator();
		curRot = GetActorRotation();
		curRot = FMath::Lerp(curRot, targetrot, 1 * DeltaTime);
		SetActorRotation(curRot);
	}

	/*Ending();*/
	if (spot)
	{
		if (bisEnd == false)
		{
			endingCurrentTime += DeltaTime;
			if (endingCurrentTime >= 5.f)
			{
				GetWorld()->SpawnActor<AIcon1>(icon1Factory, GetTransform());

				SetActorHiddenInGame(true);

				//SetActorRotation(dir.ToOrientationRotator());
				bisEnd = true;
			}
		}
	}

	if (pointMachine)
	{
		if (pointMachine->bisTouch1 == true)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effectFactory, GetActorLocation() + FVector(0.f, 0.0f, 0.f));
			pointMachine->bisTouch1 = false;
		}
	}
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

	float amountOnParam = FMath::Lerp(0.0f, 1.0f, playTime);

	watch->SetScalarParameterValueOnMaterials(TEXT("Amount"), amountOnParam * 0.5);
	watch->SetScalarParameterValueOnMaterials(TEXT("Boost"), amountOnParam * 0.5);
	watch->SetScalarParameterValueOnMaterials(TEXT("Fringe Width"), amountOnParam * 0.5);


	if (playTime >= 2.0f)
	{
		playTime = 0;

		SetState(EBlinkState::UnBlink);
	}
}

void AWatch1::UnBlink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	float boostOffParam = FMath::Lerp(1.0f,0.0f, playTime);

	watch->SetScalarParameterValueOnMaterials(TEXT("Boost"), boostOffParam * 0.49);
	watch->SetScalarParameterValueOnMaterials(TEXT("Fringe Width"), boostOffParam * 0.5);

	if (playTime >= 2.0f)
	{
		isBlink = false;

		watch->SetScalarParameterValueOnMaterials(TEXT("Amount"), 1.0f);
		watch->SetScalarParameterValueOnMaterials(TEXT("Boost"), 0.1f);
		watch->SetScalarParameterValueOnMaterials(TEXT("Fringe Width"), 0.0f);

		playTime = 0;
		SetState(EBlinkState::Idle);
	}
}

void AWatch1::WatchLookat()
{
	SetActorRotation(dir.ToOrientationRotator());
}

