// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch3.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "Components/StaticMeshComponent.h"
#include "IconSpot.h"
#include "Icon3.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "SJ_Actor_KnowledgePoint.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
AWatch3::AWatch3()
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
void AWatch3::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	spot = Cast<AIconSpot>(UGameplayStatics::GetActorOfClass(GetWorld(), AIconSpot::StaticClass()));
	icon3 = Cast<AIcon3>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon3::StaticClass()));
	pointMachine = Cast<ASJ_Actor_KnowledgePoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_KnowledgePoint::StaticClass()));
}

// Called every frame
void AWatch3::Tick(float DeltaTime)
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
		curRot = FMath::Lerp(curRot, targetrot, 5 * DeltaTime);
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
				GetWorld()->SpawnActor<AIcon3>(icon3Factory, GetTransform());

				SetActorHiddenInGame(true);

				//SetActorRotation(dir.ToOrientationRotator());
				bisEnd = true;
			}
		}
	}
}

EBlinkState AWatch3::GetState()
{
	return EBlinkState();
}

void AWatch3::SetState(EBlinkState state)
{
	blinkState = state;
}

void AWatch3::Idle()
{
	if (isBlink == true)
	{
		nia->SetActive(true);
		UGameplayStatics::PlaySound2D(GetWorld(), ddirorongSound);
		SetState(EBlinkState::Blink);
		isBlink = false;
	}
}

void AWatch3::Blink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	float amountOnParam = FMath::Lerp(0.0f, 1.0f, playTime);
	float fixedOnParam = 1.0f;
	float fixedBoostOnParam = 30.0f;

	watch->SetScalarParameterValueOnMaterials(TEXT("Amount"), fixedOnParam);
	watch->SetScalarParameterValueOnMaterials(TEXT("Boost"), fixedBoostOnParam);
	watch->SetScalarParameterValueOnMaterials(TEXT("Fringe Width"), fixedOnParam);


	if (playTime >= 2.0f)
	{
		playTime = 0;

		SetState(EBlinkState::UnBlink);
	}
}

void AWatch3::UnBlink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	float boostOffParam = FMath::Lerp(30.0f, 0.1f, playTime);
	float offParam = FMath::Lerp(1.0f, 0.0f, playTime);

	watch->SetScalarParameterValueOnMaterials(TEXT("Boost"), boostOffParam * 14.9f);
	watch->SetScalarParameterValueOnMaterials(TEXT("Fringe Width"), offParam * 0.5f);

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

