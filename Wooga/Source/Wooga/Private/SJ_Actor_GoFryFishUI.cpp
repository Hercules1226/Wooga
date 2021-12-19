// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_GoFryFishUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_GoFryFishUI::ASJ_Actor_GoFryFishUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	goFryFishUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	goFryFishUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_GoFryFishUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(4386, 6752, 1252);

	SetActorLocation(p);

	FRotator r = FRotator(0, 29, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_GoFryFishUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

