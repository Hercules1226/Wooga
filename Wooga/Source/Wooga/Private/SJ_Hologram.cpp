 // Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Hologram.h"
#include <Components/StaticMeshComponent.h>
#include "VR_Player.h"
#include "SJ_WoogaGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include <Components/PostProcessComponent.h>
#include "Watch.h"
#include <Components/WidgetComponent.h>
#include "SJ_Actor_KnowledgePoint.h"

// Sets default values
ASJ_Hologram::ASJ_Hologram()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	holoPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hologram"));
	holoPlane->SetupAttachment(rootComp);

	holoPost = CreateDefaultSubobject<UPostProcessComponent>(TEXT("HologramPostProcess"));
	// holoPost->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Hologram::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(GetWorld(), onSound);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	watch = Cast<AWatch>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch::StaticClass()));
	
	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	FVector playerLoc = player->GetActorLocation();
	FVector me = GetActorLocation();

	FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 300;

	// ºÒÀÇ ¹ß°ß È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::Firing || gameMode->flowState == EFlowState::CompleteFireDiscovery)
	{
		FVector p1 = FVector(10731, 11813, 1320);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 75, 0);

		SetActorRotation(r1);
		
		playChangeTime = 9;
	}

	// Ã¤Áý È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::CollectAndEat || gameMode->flowState == EFlowState::CompleteCollect)
	{
		FVector p2 = FVector(9568, 9984, 1322);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 80, 0);

		SetActorRotation(r2);

		playChangeTime = 6;
	}

	// ÁÖ¸Ôµµ³¢ È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::CompleteHandAx || gameMode->flowState == EFlowState::DirectlyHit)
	{
		FVector p3 = FVector(7874, 9004, 1320);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 43, 0);

		SetActorRotation(r3);

		playChangeTime = 9;
	}
	// ºÒÀÇ È°¿ë È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::EatMeat || gameMode->flowState == EFlowState::CompleteFireUse)
	{
		FVector p4 = FVector(6292, 6927, 1320);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, 73, 0);

		SetActorRotation(r4);

		playChangeTime = 12;
	}
	// ½¿º£Âî¸£°³ È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::TieSpear || gameMode->flowState == EFlowState::CompleteSpear)
	{
		FVector p5 = FVector(4546, 6926, 1334);

		SetActorLocation(p5);

		FRotator r5 = FRotator(-5, -32, 0);

		SetActorRotation(r5);

		playChangeTime = 9;
	}
	// ¿òÁý È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::MakeHut || gameMode->flowState == EFlowState::CompleteHut)
	{
		FVector p6  = FVector(7051, 6747, 1330);

		SetActorLocation(p6);

		FRotator r6 = FRotator(0, 128, 0);

		SetActorRotation(r6);

		playChangeTime = 14;
	}

	SetState(EHologramState::TurnOnHologram);
}

// Called every frame
void ASJ_Hologram::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (holoState)
	{
	case EHologramState::TurnOnHologram:
		TurnOnHologram();
		break;
	case EHologramState::PlayHologram:
		PlayHologram();
		break;
	case EHologramState::TurnOffHologram:
		TurnOffHologram();
		break;
	}
}

void ASJ_Hologram::SetState(EHologramState state)
{
	holoState = state;
}

EHologramState ASJ_Hologram::GetState()
{
	return EHologramState();
}

void ASJ_Hologram::TurnOnHologram()
{
	// È¦·Î±×·¥ »ý¼º
	createTime +=GetWorld()->DeltaTimeSeconds;

	startParam = FMath::Lerp(-1.0f, 1.0f, createTime);

	holoPlane->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), startParam);

	if (createTime >= 1.0f)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FDHologramSound);
		createTime = 0;

		SetState(EHologramState::PlayHologram);
	}
}

void ASJ_Hologram::PlayHologram()
{
	// È¦·Î±×·¥ ÇÃ·¹ÀÌ ½Ã°£¿¡ ¸ÂÃç ¼³Á¤
	playTime += GetWorld()->DeltaTimeSeconds;

	if (playTime >= playChangeTime)
	{
		playTime = 0;
		// È¦·Î±×·¥ ºñÈ°¼ºÈ­ ÄÚµå
		// holoPost-> bEnabled = false;

		 SetState(EHologramState::TurnOffHologram);
	}
}

void ASJ_Hologram::TurnOffHologram()
{
	destroyTime += GetWorld()->DeltaTimeSeconds;

	if (destroyTime >= 2.0f)
	{
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ASJ_Actor_KnowledgePoint>(bpKnowledgePoint, GetActorLocation(), GetActorRotation(), Param);

		destroyTime = 0;
		Destroy();
	}
}


