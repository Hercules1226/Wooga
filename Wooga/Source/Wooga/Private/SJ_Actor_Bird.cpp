// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_Bird.h"
#include <Components/BoxComponent.h>

// Sets default values
ASJ_Actor_Bird::ASJ_Actor_Bird()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	destroyZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyZone"));
	destroyZone->SetupAttachment(rootComp);

	bird = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bird"));
	bird->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_Bird::BeginPlay()
{
	Super::BeginPlay();
	
	destroyZone->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_Bird::OnBirdEnter);

	isFly = false;
	SetActorHiddenInGame(true);
}

// Called every frame
void ASJ_Actor_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isFly == true)
	{
		FVector me = bird->GetComponentLocation();
		FVector tar = destroyZone->GetComponentLocation();
		FVector dir = tar - me;
		dir.Normalize();

		FVector p = me + dir * speed * DeltaTime;

		SetActorLocation(p);

		// bird->SetRelativeLocation(p);

		currentTime += DeltaTime;

		if (currentTime >= 5)
		{
			Destroy();
		}

	}
}

void ASJ_Actor_Bird::OnBirdEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp == bird)
	{
		Destroy();
	}
}

void ASJ_Actor_Bird::Fly()
{
	isFly = true;
	SetActorHiddenInGame(false);
}

