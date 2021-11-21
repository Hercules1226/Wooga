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
		FVector p = FVector(7600, 8717, 1190);

		SetActorLocation(p);

		FRotator r = FRotator(0, -40, 0);

		SetActorRotation(r);
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

	if (gameMode->flowState == EFlowState::CuttingPig)
	{
		// ���� �ڸ���
		FVector p1 = FVector(7333, 8431, 1190);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, -30, 0);

		SetActorRotation(r1);
	}

	if (gameMode->flowState == EFlowState::MakeSpear)
	{
		// ������� �����
		FVector p2 = FVector(4392, 6799, 1210);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 90, 0);

		SetActorRotation(r2);
	}
}

void ASJ_Actor_MakeRange::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (OtherActor == player)
	{
		isPlayerIn = true;

		UE_LOG(LogTemp, Warning, TEXT("PlayerIn"));
	}
}

