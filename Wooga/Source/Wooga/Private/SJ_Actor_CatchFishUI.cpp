// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_CatchFishUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_CatchFishUI::ASJ_Actor_CatchFishUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	catchFishUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	catchFishUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_CatchFishUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p =FVector(3910, 6187, 1245);

	SetActorLocation(p);

	FRotator r = FRotator(0, 70, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_CatchFishUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

