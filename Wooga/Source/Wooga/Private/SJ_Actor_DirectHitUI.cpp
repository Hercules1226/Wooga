// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_DirectHitUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>


// Sets default values
ASJ_Actor_DirectHitUI::ASJ_Actor_DirectHitUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	directUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToFireUI"));
	directUI->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_DirectHitUI::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(7478, 8854, 1280);

	SetActorLocation(p);

	// FRotator r = FRotator(0, -40, 0);

	// SetActorRotation(r);
}

// Called every frame
void ASJ_Actor_DirectHitUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

