// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_PickUpMeatUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "SlicePig.h"
#include "Tomahowk.h"

// Sets default values
ASJ_Actor_PickUpMeatUI::ASJ_Actor_PickUpMeatUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	pickUpMeatUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	pickUpMeatUI->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_PickUpMeatUI::BeginPlay()
{
	Super::BeginPlay();
	
	tomahowk = Cast<ATomahowk>(UGameplayStatics::GetActorOfClass(GetWorld(), ATomahowk::StaticClass()));

	FVector pigLoc = tomahowk->GetActorLocation();
	// FVector p = pigLoc + FVector::UpVector * 100;
	FVector p = FVector(7775, 8729, 1290);
	SetActorLocation(p);

	FRotator r = FRotator(0, 81, 0);
	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_PickUpMeatUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

