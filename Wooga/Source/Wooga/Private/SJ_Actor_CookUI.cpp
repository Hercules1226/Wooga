// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_CookUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_CookUI::ASJ_Actor_CookUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	cookUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	cookUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_CookUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(5170, 7985, 1290);

	SetActorLocation(p);

	FRotator r = FRotator(0, -80, 0);

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_CookUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

