// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_Hologram.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "SJ_WoogaGameModeBase.h"

// Sets default values
ASJ_Actor_Hologram::ASJ_Actor_Hologram()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	handAxHologram = CreateDefaultSubobject<UWidgetComponent>(TEXT("HandAxHologram"));
	handAxHologram->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_Hologram::BeginPlay()
{
	Super::BeginPlay();

	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameModeBase->flowState == EFlowState::CompleteHandAx || gameModeBase->flowState == EFlowState::DirectlyHit)
	{
		FVector p3 = FVector(7370, 8030, 1320);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 50, 0);

		SetActorRotation(r3);
	}
	
}

// Called every frame
void ASJ_Actor_Hologram::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

