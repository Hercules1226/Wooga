// Fill out your copyright notice in the Description page of Project Settings.


#include "Icon1.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AIcon1::AIcon1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);

	icon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon"));
	icon->SetupAttachment(meshComp);
}

// Called when the game starts or when spawned
void AIcon1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIcon1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector me = meshComp->GetComponentLocation();
	//FVector target = spot1->GetActorLocation();
	//FVector dir = target - me;
	//dir.Normalize();
	float speed = 100.0f;

	//FVector p = me + dir * speed * DeltaTime;
	
	//SetActorLocation(p);

	FVector startScale = GetActorScale3D();
	FVector endScale = FVector(3.f, 3.f, 3.f);

	FVector setScale = FMath::Lerp(startScale, endScale, DeltaTime);

	SetActorScale3D(setScale);
}

