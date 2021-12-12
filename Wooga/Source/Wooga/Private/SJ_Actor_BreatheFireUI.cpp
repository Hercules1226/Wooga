// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_BreatheFireUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "FireStraw.h"

// Sets default values
ASJ_Actor_BreatheFireUI::ASJ_Actor_BreatheFireUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	howToFireUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	howToFireUI->SetupAttachment(rootComp);
	howToFireUI->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ASJ_Actor_BreatheFireUI::BeginPlay()
{
	Super::BeginPlay();
	fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	FVector tar = fireStraw->GetActorLocation();
	FVector me = GetActorLocation();

	FVector p = tar + fireStraw->GetActorUpVector() * 50;
	FVector p1 = FVector(10770, 12063, 1271);

	SetActorLocation(p1);

	FRotator r = FRotator(0, -73, 0);

	SetActorRotation(r);	
	
}

// Called every frame
void ASJ_Actor_BreatheFireUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

