// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockWall.h"
#include "VR_Player.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABlockWall::ABlockWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void ABlockWall::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
}

// Called every frame
void ABlockWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player)
	{
		playerPos = player->capsuleComp->GetRelativeLocation();
		wallPos = meshComp->GetRelativeLocation();

		if (FVector::Dist(wallPos, playerPos) < 500.f)
		{
			meshComp->SetHiddenInGame(false);
		}

		else if (FVector::Dist(wallPos, playerPos) >= 500.f)
		{
			meshComp->SetHiddenInGame(true);
		}
	}
}

