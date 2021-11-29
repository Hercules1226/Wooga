// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_EatFishUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_EatFishUI::ASJ_Actor_EatFishUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	eatFishUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	eatFishUI->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_EatFishUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(5254, 8061, 1310);

	SetActorLocation(p);

	FRotator r = FRotator(0, -130, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_EatFishUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

