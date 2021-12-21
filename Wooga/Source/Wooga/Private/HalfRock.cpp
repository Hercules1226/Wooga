// Fill out your copyright notice in the Description page of Project Settings.


#include "HalfRock.h"
#include "FistAxe.h"
#include "VR_Player.h"
#include "GrabActorComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AHalfRock::AHalfRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	halfRock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("halfRock"));
	SetRootComponent(halfRock);

	onMa = CreateDefaultSubobject<UMaterial>(TEXT("On Ma"));
}

// Called when the game starts or when spawned
void AHalfRock::BeginPlay()
{
	Super::BeginPlay();

	fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
}

// Called every frame
void AHalfRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (fistAxe->bisD15 == true)
	{
		SetActorHiddenInGame(true);
		player->grabComp->RightHalfRockReleaseAction();
	}
}

