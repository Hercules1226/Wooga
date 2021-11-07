// Fill out your copyright notice in the Description page of Project Settings.


#include "DetachRock.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADetachRock::ADetachRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ADetachRock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADetachRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

