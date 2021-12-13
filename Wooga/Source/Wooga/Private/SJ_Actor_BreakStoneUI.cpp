// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_BreakStoneUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_BreakStoneUI::ASJ_Actor_BreakStoneUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	breakStoneUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	breakStoneUI->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_BreakStoneUI::BeginPlay()
{
	Super::BeginPlay();

	FVector p = FVector(5191, 6533, 1272);

	SetActorLocation(p);

	FRotator r = FRotator(0, 60, 0);

	SetActorRotation(r);
	
}

// Called every frame
void ASJ_Actor_BreakStoneUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

