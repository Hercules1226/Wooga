// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_TieSpearUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_TieSpearUI::ASJ_Actor_TieSpearUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	tieSpearUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	tieSpearUI->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_TieSpearUI::BeginPlay()
{
	Super::BeginPlay();

	FVector p = FVector(5191, 6533, 1272);

	SetActorLocation(p);

	FRotator r = FRotator(0, 55, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_TieSpearUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

