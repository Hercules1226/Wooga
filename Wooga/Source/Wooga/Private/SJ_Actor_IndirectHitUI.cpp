// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_IndirectHitUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

// Sets default values
ASJ_Actor_IndirectHitUI::ASJ_Actor_IndirectHitUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	indirectUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	indirectUI->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_IndirectHitUI::BeginPlay()
{
	Super::BeginPlay();

	FVector p = FVector(7528, 8854, 1280);

	SetActorLocation(p);

	FRotator r = FRotator(0, -62, 0);

	SetActorRotation(r);
	
}

// Called every frame
void ASJ_Actor_IndirectHitUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

