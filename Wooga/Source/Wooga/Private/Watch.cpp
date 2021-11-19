// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AWatch::AWatch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(rootComp);

	watch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Watch"));
	watch->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AWatch::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
}

// Called every frame
void AWatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector dir = player->camLoc->GetRelativeLocation() - rootComp->GetRelativeLocation();
	dir.Normalize();
	SetActorRotation(dir.ToOrientationRotator());
}

