// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_BoarHitRock.h"
#include  <Components/StaticMeshComponent.h>

// Sets default values
ASJ_Actor_BoarHitRock::ASJ_Actor_BoarHitRock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock"));
	SetRootComponent(rock);
}

// Called when the game starts or when spawned
void ASJ_Actor_BoarHitRock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASJ_Actor_BoarHitRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

