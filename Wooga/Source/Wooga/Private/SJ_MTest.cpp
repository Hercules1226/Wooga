// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_MTest.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
ASJ_MTest::ASJ_MTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void ASJ_MTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASJ_MTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	propTime += DeltaTime;

	prop = FMath::Lerp(0.0f, 1.0f, propTime * 0.3f);
	meshComp->SetScalarParameterValueOnMaterials(TEXT("Amount"), prop);
}

