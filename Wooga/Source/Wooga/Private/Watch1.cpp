// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch1.h"
#include "VR_Player.h"
#include "Components/StaticMeshComponent.h"
#include "IconSpot.h"
#include "FireEvent.h"
#include "Icon1.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>

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
	spot = Cast<AIconSpot>(UGameplayStatics::GetActorOfClass(GetWorld(), AIconSpot::StaticClass()));
	icon1 = Cast<AIcon1>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon1::StaticClass()));
}

// Called every frame
void AWatch1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += DeltaTime;
	if (player->camLoc)
	{
		//if (currentTime >= 1.f)
		{
			dir = player->camLookAt->GetComponentLocation() - watch->GetComponentLocation();
			dir.Normalize();
			currentTime = 0;
		}
		WatchLookat();
		/*Ending();*/

		if (bisEnd == false)
		{
			endingCurrentTime += DeltaTime;
			if (endingCurrentTime >= 5.f)
			{
				GetWorld()->SpawnActor<AIcon1>(icon1Factory, GetTransform());

				SetActorHiddenInGame(true);

				//SetActorRotation(dir.ToOrientationRotator());
				bisEnd = true;
			}
		}
	}
}

void AWatch1::WatchLookat()
{
	SetActorRotation(dir.ToOrientationRotator());
}

void AWatch1::Ending()
{

}

