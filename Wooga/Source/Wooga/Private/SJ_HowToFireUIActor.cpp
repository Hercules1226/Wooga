// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_HowToFireUIActor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_HowToFireUIActor::ASJ_HowToFireUIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	howToFireUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	howToFireUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_HowToFireUIActor::BeginPlay()
{
	Super::BeginPlay();

	FVector f = FVector(11176, 11985, 1277);
	SetActorLocation(f);
}

// Called every frame
void ASJ_HowToFireUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_HowToFireUIActor::Activate()
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(false);
}

void ASJ_HowToFireUIActor::Deactivate()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(true);
}



