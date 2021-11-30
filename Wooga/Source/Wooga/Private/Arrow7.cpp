// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow7.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AArrow7::AArrow7()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AArrow7::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
}

// Called every frame
void AArrow7::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (currentTime >= 2.f)
	{
		meshComp->SetHiddenInGame(false);
	}

	if (arrowOn == true)
	{
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
	}

	if (arrowOn == false)
	{
		meshComp->SetHiddenInGame(true);
	}
}

