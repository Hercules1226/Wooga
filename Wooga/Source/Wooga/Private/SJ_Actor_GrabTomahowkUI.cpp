// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_GrabTomahowkUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_GrabTomahowkUI::ASJ_Actor_GrabTomahowkUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	grabTomahowkUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	grabTomahowkUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_GrabTomahowkUI::BeginPlay()
{
	Super::BeginPlay();

	FVector p = FVector(6338, 6963, 1345);

	SetActorLocation(p);

	FRotator r = FRotator(0, 73, 0);

	SetActorRotation(r);
	
}

// Called every frame
void ASJ_Actor_GrabTomahowkUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

