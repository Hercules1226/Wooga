// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_LevelLight.h"
#include <Components/DirectionalLightComponent.h>

// Sets default values
ASJ_Actor_LevelLight::ASJ_Actor_LevelLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	directLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectLight"));
	directLight->SetupAttachment(rootComp);

	sun = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Sun"));
	sun->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_LevelLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASJ_Actor_LevelLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	curDirColor = directLight->GetLightColor();
	curSunColor = sun->GetLightColor();

}

