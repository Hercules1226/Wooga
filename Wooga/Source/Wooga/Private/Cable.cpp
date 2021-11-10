// Fill out your copyright notice in the Description page of Project Settings.


#include "Cable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ACable::ACable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	stickComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stick Component"));
	SetRootComponent(stickComp);
	cableComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cable Component"));
	cableComp->SetupAttachment(stickComp);
	splineComp = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	splineComp->SetupAttachment(stickComp);

}

// Called when the game starts or when spawned
void ACable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

