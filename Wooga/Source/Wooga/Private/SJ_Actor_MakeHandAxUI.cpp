// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_MakeHandAxUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "SlicePig.h"

// Sets default values
ASJ_Actor_MakeHandAxUI::ASJ_Actor_MakeHandAxUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	makeHandAxUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	makeHandAxUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_MakeHandAxUI::BeginPlay()
{
	Super::BeginPlay();
	
	slicePig = Cast<ASlicePig>(UGameplayStatics::GetActorOfClass(GetWorld(), ASlicePig::StaticClass()));

	FVector pigLoc = slicePig->GetActorLocation();

	FVector p = FVector(7949, 8773, 1300);
	SetActorLocation(p);

	FRotator r = FRotator(0, 60, 0);
	SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_MakeHandAxUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

