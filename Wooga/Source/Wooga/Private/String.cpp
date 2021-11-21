// Fill out your copyright notice in the Description page of Project Settings.


#include "String.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AString::AString()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);

	outLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline"));
	outLine->SetupAttachment(meshComp);
	outLine->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AString::BeginPlay()
{
	Super::BeginPlay();
	
	outLine->SetVisibility(false);
}

// Called every frame
void AString::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

