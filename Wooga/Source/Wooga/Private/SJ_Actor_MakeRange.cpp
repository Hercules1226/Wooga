// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_MakeRange.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "VR_Player.h"
#include "SJ_WoogaGameModeBase.h"

// Sets default values
ASJ_Actor_MakeRange::ASJ_Actor_MakeRange()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	range = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	SetRootComponent(range);

	footStep = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FootStep"));
	footStep->SetupAttachment(range);
}

// Called when the game starts or when spawned
void ASJ_Actor_MakeRange::BeginPlay()
{
	Super::BeginPlay();

	range->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_MakeRange::OnPlayerOverlap);

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameMode->flowState == EFlowState::HitBoar)
	{
		FVector p = FVector(8132, 8855, 1185);

		SetActorLocation(p);

		FRotator r = FRotator(0, 84, 0);

		SetActorRotation(r);
	}
	else if (gameMode->flowState == EFlowState::HowTomakeSpear)
	{
		// ������� �����
		FVector p2 = FVector(4846, 6705, 1184);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 55, 0);

		SetActorRotation(r2);
	}
	else if (gameMode->flowState == EFlowState::CompleteSpear)
	{
		FVector p3 = FVector(4489, 6855, 1190);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 40, 0);

		SetActorRotation(r3);
	}
	else if (gameMode->flowState == EFlowState::CatchFish)
	{
		FVector p4 = FVector(6329, 7246, 1183);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, 154, 0);

		SetActorRotation(r4);
	}



}

// Called every frame
void ASJ_Actor_MakeRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlayerIn == true)
	{
		returnTime += DeltaTime;

		if (returnTime >= 3.0f)
		{
			returnTime = 0;
			isPlayerIn = false;
		}
	}
}

void ASJ_Actor_MakeRange::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (OtherActor == player)
	{
		isPlayerIn = true;
	}
}

