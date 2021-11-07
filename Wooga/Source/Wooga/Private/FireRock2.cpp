// Fill out your copyright notice in the Description page of Project Settings.


#include "FireRock2.h"
#include "VR_Player.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AFireRock2::AFireRock2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);

	// 물리 관련 설정
	boxComp->SetSimulatePhysics(true);
	boxComp->SetEnableGravity(true);
	boxComp->SetCollisionProfileName(TEXT("PickUp"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);

	outLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline"));
	outLine->SetupAttachment(meshComp);
	outLine->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AFireRock2::BeginPlay()
{
	Super::BeginPlay();

	outLine->SetVisibility(false);
}

// Called every frame
void AFireRock2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

