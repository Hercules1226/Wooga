// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Hologram.h"
#include <Components/StaticMeshComponent.h>
#include "VR_Player.h"
#include "SJ_WoogaGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "FireEvent.h"
#include <Components/PostProcessComponent.h>

// Sets default values
ASJ_Hologram::ASJ_Hologram()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(rootComp);
	meshComp->CreateDynamicMaterialInstance(0);

	holoPost = CreateDefaultSubobject<UPostProcessComponent>(TEXT("HologramPostProcess"));
	holoPost->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Hologram::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	FVector playerLoc = player->GetActorLocation();
	FVector me = GetActorLocation();

	FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 300;

	// ºÒÀÇ ¹ß°ß È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::Firing || gameMode->flowState == EFlowState::CompleteFireDiscovery)
	{
		FVector p1 = FVector(10875, 11859, 1290);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 70, 0);

		SetActorRotation(r1);
	}

	// Ã¤Áý È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::CollectAndEat || gameMode->flowState == EFlowState::CompleteCollect)
	{
		FVector p2 = FVector(9575, 10053, 1280);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 50, 0);

		SetActorRotation(r2);

		playChangeTime = 10.0f;
	}

	// ÁÖ¸Ôµµ³¢ È¦·Î±×·¥
	if (gameMode->flowState == EFlowState::CompleteHandAx || gameMode->flowState == EFlowState::DirectlyHit)
	{
		FVector p3 = FVector(7370, 8030, 1320);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 50, 0);

		SetActorRotation(r3);
	}

	/*
	 FVector dir = player->GetActorLocation() - GetActorLocation();
	dir.Normalize();

	SetActorRotation(dir.Rotation());
	*/
	
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

	startParam = FMath::Lerp(-0.4f, 0.5f, createTime * 0.5f);

	meshComp->SetScalarParameterValueOnMaterials(TEXT("Time"), startParam);

	if (createTime >= 2.0f)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), FDHologramSound);
		createTime = 0;

		// holoPost->bEnabled = false;
		SetState(EHologramState::PlayHologram);
	}
}

void ASJ_Hologram::PlayHologram()
{
	// È¦·Î±×·¥ ÇÃ·¹ÀÌ ½Ã°£¿¡ ¸ÂÃç ¼³Á¤
	playTime += GetWorld()->DeltaTimeSeconds;

	if (playTime >= playChangeTime)
	{
		SetState(EHologramState::TurnOffHologram);

		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AFireEvent>(knowledgePoint,  GetActorLocation(), GetActorRotation(), Param);

		playTime = 0;
	}
}

void ASJ_Hologram::TurnOffHologram()
{
	destroyTime += GetWorld()->DeltaTimeSeconds;

	destroyParam = FMath::Lerp(0.5f, -0.4f, destroyTime * 0.5f);

	meshComp->SetScalarParameterValueOnMaterials(TEXT("Time"), destroyParam);

	if (player->isKnowledgeIn == true)
	{
		destroyTime = 0;
		SetState(EHologramState::TurnOnHologram);
		player->isKnowledgeIn = false;
		Destroy();
	}
}


