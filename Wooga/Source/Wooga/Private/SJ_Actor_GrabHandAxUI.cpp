// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_GrabHandAxUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "FistAxe.h"
#include "VR_Player.h"

// Sets default values
ASJ_Actor_GrabHandAxUI::ASJ_Actor_GrabHandAxUI()
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
void ASJ_Actor_GrabHandAxUI::BeginPlay()
{
	Super::BeginPlay();
	
	fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	FVector me = GetActorLocation();
	FVector playerLoc = player->GetActorLocation();
	FVector axeLoc = fistAxe->GetActorLocation();

	// FVector p = axeLoc + FVector::UpVector * 50.0f;

	FVector p = FVector(7770, 8980, 1280);

	SetActorLocation(p);

	FRotator r = FRotator(0, -90, 0);

	FVector dir = playerLoc - me;
	dir.Normalize();

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_GrabHandAxUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

