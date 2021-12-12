// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_HowToFireNextUIActor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_HowToFireNextUIActor::ASJ_HowToFireNextUIActor()
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
void ASJ_HowToFireNextUIActor::BeginPlay()
{
	Super::BeginPlay();
	
	FVector f = FVector(11176, 11985, 1277);
	SetActorLocation(f);
}

// Called every frame
void ASJ_HowToFireNextUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

