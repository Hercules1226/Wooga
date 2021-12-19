// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_HuntFishUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_HuntFishUI::ASJ_Actor_HuntFishUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	huntFishUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	huntFishUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_HuntFishUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(4460, 6889, 1298);

	SetActorLocation(p);

	FRotator r = FRotator(0, -30, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_HuntFishUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

