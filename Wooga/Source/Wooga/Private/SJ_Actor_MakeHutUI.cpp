// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_MakeHutUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_MakeHutUI::ASJ_Actor_MakeHutUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	makeHutUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	makeHutUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_MakeHutUI::BeginPlay()
{
	Super::BeginPlay();

	FVector p = FVector(3830, 8036, 1410);

	SetActorLocation(p);

	FRotator r = FRotator(0, -75, 0);

	SetActorRotation(r);
	
}

// Called every frame
void ASJ_Actor_MakeHutUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

