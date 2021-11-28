// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalTest.h"
#include <Components/BoxComponent.h>
#include <Components/DecalComponent.h>

// Sets default values
ADecalTest::ADecalTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);
	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	boxComp->SetupAttachment(rootComp);

	decal = CreateDefaultSubobject<UDecalComponent>(TEXT("TestDecal"));
	decal->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ADecalTest::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ADecalTest::OnOverlap);
}

// Called every frame
void ADecalTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADecalTest::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

