// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_EatMeatUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_EatMeatUI::ASJ_Actor_EatMeatUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	eatUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	eatUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_EatMeatUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(6353, 7075, 1290);

	SetActorLocation(p);

	FRotator r = FRotator(0, 64, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_EatMeatUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

