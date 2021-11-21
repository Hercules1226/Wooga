// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEndingActor::AEndingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	holo1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Holo1"));
	SetRootComponent(holo1);

	holo2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Holo2"));
	holo2->SetupAttachment(holo1);

	holo3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Holo3"));
	holo3->SetupAttachment(holo1);

	holo4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Holo4"));
	holo4->SetupAttachment(holo1);

	holo5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Holo5"));
	holo5->SetupAttachment(holo1);

	holo6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Holo6"));
	holo6->SetupAttachment(holo1);
}

// Called when the game starts or when spawned
void AEndingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

