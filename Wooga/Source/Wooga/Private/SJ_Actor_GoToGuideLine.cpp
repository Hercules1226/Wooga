// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_GoToGuideLine.h"
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>
#include "VR_Player.h"
#include "SJ_WoogaGameModeBase.h"


// Sets default values
ASJ_Actor_GoToGuideLine::ASJ_Actor_GoToGuideLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	informUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("InformUI"));
	informUI->SetupAttachment(rootComp);

	range = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	range->SetupAttachment(rootComp);

	footHold = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FootHold"));
	footHold->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_GoToGuideLine::BeginPlay()
{
	Super::BeginPlay();
	
	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameModeBase->flowState == EFlowState::SpawnCollectGuideLine)
	{
		FVector p1 = FVector(9897.0f, 10207.0f, 1260.0);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 58, 0);

		SetActorRotation(r1);
	}
	else if (gameModeBase->flowState == EFlowState::SpawnHandAxGuideLine)
	{
		FVector p2 = FVector(8038, 8928, 1260);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 50, 0);

		SetActorRotation(r2);
	}
	else if (gameModeBase->flowState == EFlowState::CuttingPig)
	{
		FVector p3 = FVector(5279, 7747, 1260);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, -50, 0);

		SetActorRotation(r3);
	}
	else if (gameModeBase->flowState == EFlowState::CompleteFireUse || gameModeBase->flowState == EFlowState::GoToSpear || gameModeBase->flowState == EFlowState::TestFunc)
	{
		FVector p4 = FVector(4219, 6887, 1260);
		
		SetActorLocation(p4);

		FRotator r4 = FRotator(0, 70, 0);

		SetActorRotation(r4);
	}
	else if (gameModeBase->flowState == EFlowState::EatFish || gameModeBase->flowState == EFlowState::GoToHut)
	{
		FVector p5 = FVector(4207, 7727, 1260);

		SetActorLocation(p5);

		FRotator r5 = FRotator(0, -50, 0);

		SetActorRotation(r5);
	}

	range->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_GoToGuideLine::RangeIn);
}

// Called every frame
void ASJ_Actor_GoToGuideLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isTrigger == true)
	{
		changeTime += DeltaTime;

		if (changeTime >= 0.1f)
		{
			isTrigger = false;
			changeTime = 0;
		}
	}
}

void ASJ_Actor_GoToGuideLine::RangeIn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (player)
	{
		isTrigger = true;
	}
}