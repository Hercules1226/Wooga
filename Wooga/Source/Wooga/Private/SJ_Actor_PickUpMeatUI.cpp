// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_PickUpMeatUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "SlicePig.h"

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
	
	slicePig = Cast<ASlicePig>(UGameplayStatics::GetActorOfClass(GetWorld(), ASlicePig::StaticClass()));

	FVector pigLoc = slicePig->GetActorLocation();
	FVector p = pigLoc + FVector::UpVector * 200;
	SetActorLocation(p);

	FRotator r = FRotator(0, -40.0f, 0);
	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_PickUpMeatUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

