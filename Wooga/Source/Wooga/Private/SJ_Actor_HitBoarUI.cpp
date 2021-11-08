// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_HitBoarUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "SJ_Character_Boar.h"

// Sets default values
ASJ_Actor_HitBoarUI::ASJ_Actor_HitBoarUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	hitBoarUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	hitBoarUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_HitBoarUI::BeginPlay()
{
	Super::BeginPlay();
	
	boar = Cast<ASJ_Character_Boar>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Character_Boar::StaticClass()));

	FVector boarLoc = boar->GetActorLocation();
	FVector p = boarLoc + boar->GetActorUpVector() * 100.0f;

	SetActorLocation(p);

	FRotator r = boar->GetActorRotation();

	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_HitBoarUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

