// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_FireTwoUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_FireTwoUI::ASJ_Actor_FireTwoUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	fireTwoUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	fireTwoUI->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_FireTwoUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(5170, 7985, 1290);

	SetActorLocation(p);

	FRotator r = FRotator(0, -80, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_FireTwoUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

