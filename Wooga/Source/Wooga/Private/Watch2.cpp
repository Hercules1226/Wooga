// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch2.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "Components/StaticMeshComponent.h"
#include "IconSpot.h"
#include "Icon2.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
AWatch2::AWatch2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	watch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Watch"));
	watch->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AWatch2::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	spot = Cast<AIconSpot>(UGameplayStatics::GetActorOfClass(GetWorld(), AIconSpot::StaticClass()));
	icon2 = Cast<AIcon2>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon2::StaticClass()));
}

// Called every frame
void AWatch2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player->camLoc)
	{

		/*if (currentTime >= 1.f)
		{
			dir = player->camLookAt->GetComponentLocation() - watch->GetComponentLocation();

			curRot = watch->GetComponentRotation();
			targetrot = dir.ToOrientationRotator();
		}*/

		FVector dir2 = player->camLookAt->GetComponentLocation() - watch->GetComponentLocation();
		dir2.Normalize();
		FRotator targetrot2 = dir2.ToOrientationRotator();
		FRotator curRot3 = watch->GetComponentRotation();
		curRot3 = FMath::Lerp(curRot3, targetrot, 5 * DeltaTime);
		watch->SetWorldRotation(curRot3);
	}

	/*if (player->camLoc)
	{
		dir = player->camLookAt->GetComponentLocation() - watch->GetComponentLocation();
		dir.Normalize();
		SetActorRotation(dir.ToOrientationRotator());

	}*/

	/*Ending();*/
	if (spot)
	{
		if (bisEnd == false)
		{
			endingCurrentTime += DeltaTime;
			if (endingCurrentTime >= 5.5f)
			{
				GetWorld()->SpawnActor<AIcon2>(icon2Factory, GetTransform());

				SetActorHiddenInGame(true);

				//SetActorRotation(dir.ToOrientationRotator());
				bisEnd = true;
			}
		}
	}
}

