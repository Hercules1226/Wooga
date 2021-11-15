// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_Hologram.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "SJ_WoogaGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"

// Sets default values
ASJ_Actor_Hologram::ASJ_Actor_Hologram()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	hologram = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hologram"));
	hologram->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_Hologram::BeginPlay()
{
	Super::BeginPlay();

	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());
	// ºÒÀÇ ¹ß°ß È¦·Î±×·¥
	if (gameModeBase->flowState == EFlowState::Firing || gameModeBase->flowState == EFlowState::CompleteFireDiscovery)
	{
		FVector p1 = FVector(10875, 11859, 1290);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 70, 0);

		SetActorRotation(r1);

		playChangeTime = 12.0f;
	}
	// Ã¤Áý È¦·Î±×·¥
	if (gameModeBase->flowState == EFlowState::CollectAndEat || gameModeBase->flowState == EFlowState::CompleteCollect)
	{
		FVector p2 = FVector(9575, 10053, 1280);

		SetActorLocation(p2);

		playChangeTime = 10.0f;
	}

	// ÁÖ¸Ôµµ³¢ È¦·Î±×·¥
	if (gameModeBase->flowState == EFlowState::CompleteHandAx || gameModeBase->flowState == EFlowState::DirectlyHit)
	{
		FVector p3 = FVector(7370, 8030, 1320);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 50, 0);

		SetActorRotation(r3);
	}
	
	SetState(EHologramState::TurnOnHologram);
}

// Called every frame
void ASJ_Actor_Hologram::Tick(float DeltaTime)
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

void ASJ_Actor_Hologram::SetState(EHologramState state)
{
	holoState = state;
}

EHologramState ASJ_Actor_Hologram::GetState()
{
	return EHologramState();
}

void ASJ_Actor_Hologram::TurnOnHologram()
{
	createTime += GetWorld()->DeltaTimeSeconds;

	if (createTime >= 2.0f)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), propSound);

		createTime = 0;
		SetState(EHologramState::PlayHologram);
	}
}

void ASJ_Actor_Hologram::PlayHologram()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	if (playTime >= playChangeTime)
	{
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AFireEvent>(knowledgePoint, GetActorLocation(), GetActorRotation(), Param);

		playTime = 0;

		SetState(EHologramState::TurnOffHologram);
	}
}

void ASJ_Actor_Hologram::TurnOffHologram()
{
	destroyTime += GetWorld()->DeltaTimeSeconds;

	if (destroyTime >= 3.0f)
	{
		destroyTime = 0;
		SetState(EHologramState::TurnOnHologram);
		Destroy();
	}
}

