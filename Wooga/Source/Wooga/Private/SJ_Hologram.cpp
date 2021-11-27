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
#include "Watch.h"
#include <Components/WidgetComponent.h>

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

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	watch = Cast<AWatch>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch::StaticClass()));
	
	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	FVector playerLoc = player->GetActorLocation();
	FVector me = GetActorLocation();

	FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 300;

	// ���� �߰� Ȧ�α׷�
	if (gameMode->flowState == EFlowState::Firing || gameMode->flowState == EFlowState::CompleteFireDiscovery)
	{
		FVector p1 = FVector(10874, 11825, 1290);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 70, 0);

		SetActorRotation(r1);
	}

	// ä�� Ȧ�α׷�
	if (gameMode->flowState == EFlowState::CollectAndEat || gameMode->flowState == EFlowState::CompleteCollect)
	{
		FVector p2 = FVector(9476, 10068, 1315);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 50, 0);

		SetActorRotation(r2);

		playChangeTime = 10.0f;
	}

	// �ָԵ��� Ȧ�α׷�
	if (gameMode->flowState == EFlowState::CompleteHandAx || gameMode->flowState == EFlowState::DirectlyHit)
	{
		FVector p3 = FVector(7513, 8548, 1340);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 25, 0);

		SetActorRotation(r3);

		playChangeTime = 12.0f;
	}
	// ���� Ȱ�� Ȧ�α׷�
	if (gameMode->flowState == EFlowState::EatMeat || gameMode->flowState == EFlowState::CompleteFireUse)
	{
		FVector p4 = FVector(4998, 8021, 1280);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, -40, 0);

		SetActorRotation(r4);

		playChangeTime = 21.0f;
	}
	// ������� Ȧ�α׷�
	if (gameMode->flowState == EFlowState::TieSpear || gameMode->flowState == EFlowState::CompleteSpear)
	{
		FVector p5 = FVector(4110, 6760, 1280);

		SetActorLocation(p5);

		playChangeTime = 13.0f;
	}
	// ���� Ȧ�α׷�
	if (gameMode->flowState == EFlowState::MakeHut || gameMode->flowState == EFlowState::CompleteHut)
	{
		FVector p6  = FVector(3783, 7816, 1290);

		SetActorLocation(p6);

		FRotator r6 = FRotator(0, -30, 0);

		SetActorRotation(r6);

		playChangeTime = 18.0f;
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
	// Ȧ�α׷� ����
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
	// Ȧ�α׷� �÷��� �ð��� ���� ����
	playTime += GetWorld()->DeltaTimeSeconds;

	if (playTime >= playChangeTime)
	{
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AFireEvent>(knowledgePoint,  GetActorLocation(), GetActorRotation(), Param);

		playTime = 0;

		Destroy();
		// Ȧ�α׷� ��Ȱ��ȭ �ڵ�
		// holoPost-> bEnabled = false;

		 // SetState(EHologramState::TurnOffHologram);
	}
}

void ASJ_Hologram::TurnOffHologram()
{
	destroyTime += GetWorld()->DeltaTimeSeconds;

	if (destroyTime >= 1.0f)
	{
		destroyTime = 0;
		Destroy();
	}
}


