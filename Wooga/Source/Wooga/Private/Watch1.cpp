// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch1.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
AWatch1::AWatch1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	watch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Watch"));
	watch->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AWatch1::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
}

// Called every frame
void AWatch1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime+= DeltaTime;
	if (player->camLoc)
	{
		//if (currentTime >= 1.f)
		{
			dir = player->camLookAt->GetComponentLocation() - watch->GetComponentLocation();
			dir.Normalize();
			currentTime = 0;
		}
		WatchLookat();

		//SetActorRotation(dir.ToOrientationRotator());

	}

	// ending
	/*
	if (bisEnd == false)
	{
		currentTime += DeltaTime;
		if (currentTime >= 5.f)
		{
			/*watch->SetHiddenInGame(true);

			bisEnd = true;
		}
	}
	*/
}

void AWatch1::WatchLookat()
{
	SetActorRotation(dir.ToOrientationRotator());
}

