// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch5.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "Components/StaticMeshComponent.h"
#include "IconSpot.h"
#include "Icon5.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
AWatch5::AWatch5()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	watch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Watch"));
	watch->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AWatch5::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	spot = Cast<AIconSpot>(UGameplayStatics::GetActorOfClass(GetWorld(), AIconSpot::StaticClass()));
	icon5 = Cast<AIcon5>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon5::StaticClass()));
}

// Called every frame
void AWatch5::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player->camLoc)
	{
		FVector dir = player->camLookAt->GetComponentLocation() - watch->GetComponentLocation();
		dir.Normalize();
		SetActorRotation(dir.ToOrientationRotator());
	}

	/*Ending();*/
	if (spot)
	{
		if (bisEnd == false)
		{
			endingCurrentTime += DeltaTime;
			if (endingCurrentTime >= 7.f)
			{
				GetWorld()->SpawnActor<AIcon5>(icon5Factory, GetTransform());

				SetActorHiddenInGame(true);

				//SetActorRotation(dir.ToOrientationRotator());
				bisEnd = true;
			}
		}
	}
}

