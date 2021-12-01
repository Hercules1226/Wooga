// Fill out your copyright notice in the Description page of Project Settings.


#include "Icon6.h"
#include "Components/StaticMeshComponent.h"
#include "IconSpot.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AIcon6::AIcon6()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);

	icon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon"));
	icon->SetupAttachment(meshComp);
}

// Called when the game starts or when spawned
void AIcon6::BeginPlay()
{
	Super::BeginPlay();

	spot = Cast<AIconSpot>(UGameplayStatics::GetActorOfClass(GetWorld(), AIconSpot::StaticClass()));
}

// Called every frame
void AIcon6::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (spot)
	{
		FVector me = meshComp->GetComponentLocation();
		FVector target = spot->spot6->GetComponentLocation() + FVector(0.f, 0.f, 40.f);
		FVector dir = target - me;
		dir.Normalize();

		float speed = 600.0f;

		FVector p = me + dir * speed * DeltaTime;

		SetActorLocation(p);

		FVector startScale = GetActorScale3D();
		FVector endScale = FVector(15.f, 15.f, 15.f);

		FVector setScale = FMath::Lerp(startScale, endScale, DeltaTime * 2.5f);
		SetActorScale3D(setScale);

		if (FVector::Dist(me, target) < 5.f)
		{
			SetActorLocation(target);
			icon->SetHiddenInGame(true);
		}
	}
}


