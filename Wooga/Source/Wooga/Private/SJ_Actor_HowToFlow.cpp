// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_HowToFlow.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PostProcessComponent.h>

// Sets default values
ASJ_Actor_HowToFlow::ASJ_Actor_HowToFlow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	howToPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HowToPlane"));
	howToPlane->SetupAttachment(rootComp);

	howToPost = CreateDefaultSubobject<UPostProcessComponent>(TEXT("HowToPost"));
	howToPost->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_HowToFlow::BeginPlay()
{
	Super::BeginPlay();
	
	satSet.bOverride_ColorSaturation = true;
	satSet.ColorSaturation = FVector4(0.0f, 0.0f, 0.0f, 0.0f);

	howToPost->Settings = satSet;

	howToPlane->SetRenderCustomDepth(true);
	}
// Called every frame
void ASJ_Actor_HowToFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

