// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AArrow::AArrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += DeltaTime;
	if (currentTime >= 2.f)
	{
		meshComp->SetHiddenInGame(false);
	}

	if (player->camLoc)
	{
		if (meshComp->bHiddenInGame == false)
		{
			rotDir = player->camLookAt->GetComponentLocation() - GetActorLocation();
			rotDir.Normalize();
			targetrot = rotDir.ToOrientationRotator();
			curRot = GetActorRotation();
			targetRotYaw = targetrot.Yaw;
			curRot = FMath::Lerp(curRot, FRotator(90.f, targetRotYaw, 0.f), 1 * DeltaTime);

			SetActorRotation(curRot);
		}
	}

	/*if(currentTime <= 0.5f)
	{
	dir = meshComp->GetForwardVector() * pm;

	SetActorLocation(meshComp->GetComponentLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds /5);
	}
	if (currentTime > 0.5f)
	{
		pm = pm * (-1.f);
		currentTime = 0.f;
	}*/
}

