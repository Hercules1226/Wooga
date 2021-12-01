// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch5.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "Components/StaticMeshComponent.h"
#include "IconSpot.h"
#include "Icon5.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "SJ_Actor_KnowledgePoint.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
AWatch5::AWatch5()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	watch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Watch"));
	watch->SetupAttachment(rootComp);

	nia = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia"));
	nia->SetupAttachment(watch);
}

// Called when the game starts or when spawned
void AWatch5::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	spot = Cast<AIconSpot>(UGameplayStatics::GetActorOfClass(GetWorld(), AIconSpot::StaticClass()));
	icon5 = Cast<AIcon5>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon5::StaticClass()));
	pointMachine = Cast<ASJ_Actor_KnowledgePoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_KnowledgePoint::StaticClass()));
}

// Called every frame
void AWatch5::Tick(float DeltaTime)
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
		curRot = FMath::Lerp(curRot, targetrot, 9 * DeltaTime);
		SetActorRotation(curRot);
	}

	/*Ending();*/
	if (spot)
	{
		if (bisEnd == false)
		{
			endingCurrentTime += DeltaTime;
			if (endingCurrentTime >= 7.f)
			{
				GetWorld()->SpawnActor<AIcon5>(icon5Factory, GetTransform());

				SetActorHiddenInGame(true);

				//SetActorRotation(dir.ToOrientationRotator());
				bisEnd = true;
			}
		}
	}
}

EBlinkState AWatch5::GetState()
{
	return EBlinkState();
}

void AWatch5::SetState(EBlinkState state)
{
	blinkState = state;
}

void AWatch5::Idle()
{
	if (isBlink == true)
	{
		nia->SetActive(true);
		UGameplayStatics::PlaySound2D(GetWorld(), ddirorongSound);
		SetState(EBlinkState::Blink);
		isBlink = false;
	}
}

void AWatch5::Blink()
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

void AWatch5::UnBlink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	float boostOffParam = FMath::Lerp(1.0f, 0.0f, playTime);

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

