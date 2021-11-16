// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_WatchInformUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASJ_Actor_WatchInformUI::ASJ_Actor_WatchInformUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	howToFireUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	howToFireUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_WatchInformUI::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	
	FVector p1 = FVector(10850, 11859, 1280);

	SetActorLocation(p1);

	FVector dir = player->GetActorLocation() - GetActorLocation();
	dir.Normalize();

	SetActorRotation(dir.Rotation());
}

// Called every frame
void ASJ_Actor_WatchInformUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

