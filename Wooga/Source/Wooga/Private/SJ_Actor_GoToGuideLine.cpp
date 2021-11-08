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

	if (gameModeBase->flowState == EFlowState::InformWatch || gameModeBase->flowState == EFlowState::GoToCollectCourse)
	{
		FVector p1 = FVector(9897.0f, 10207.0f, 1260.0);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 58, 0);

		SetActorRotation(r1);
	}
	else if (gameModeBase->flowState == EFlowState::CompleteCollect || gameModeBase->flowState == EFlowState::GoToFistAxCourse)
	{
		FVector p2 = FVector(7473, 8344, 1270);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 60, 0);

		SetActorRotation(r2);
	}

	range->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_GoToGuideLine::RangeIn);
}

// Called every frame
void ASJ_Actor_GoToGuideLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_GoToGuideLine::RangeIn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (player)
	{
		isTrigger = true;
	}
}