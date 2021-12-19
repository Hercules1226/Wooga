// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_CookFishUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_CookFishUI::ASJ_Actor_CookFishUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	cookFishUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	cookFishUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_CookFishUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(6455, 7131, 1310);

	SetActorLocation(p);
	
	FRotator r = FRotator(0, 128, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_CookFishUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

