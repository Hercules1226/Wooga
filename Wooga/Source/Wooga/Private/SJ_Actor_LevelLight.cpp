// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_LevelLight.h"
#include <Components/DirectionalLightComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/PostProcessComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SkyLightComponent.h>

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

	skyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	skyLight->SetupAttachment(rootComp);

	skySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkySphere"));
	skySphere->SetupAttachment(rootComp);

	levelPost = CreateDefaultSubobject<UPostProcessComponent>(TEXT("LevelPost"));
	levelPost->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_LevelLight::BeginPlay()
{
	Super::BeginPlay();
	
	SetState(ELightState::Day);
}

// Called every frame
void ASJ_Actor_LevelLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	switch (lightState)
	{
	case ELightState::Stay:
		Stay();
		break;
	case ELightState::Day:
		Day();
		break;
	case ELightState::Night:
		Night();
		break;
	}
}

ELightState ASJ_Actor_LevelLight::GetState()
{
	return ELightState();
}

void ASJ_Actor_LevelLight::SetState(ELightState state)
{
	lightState = state;
}

void ASJ_Actor_LevelLight::Stay()
{
	if (isDay == true)
	{
		SetState(ELightState::Day);
	}
	else if (isNight == true)
	{
		SetState(ELightState::Night);
	}
}

void ASJ_Actor_LevelLight::Day()
{
	// 라이트 변경
	changeTIme += GetWorld()->DeltaTimeSeconds;

	curDirColor = FMath::Lerp(curDirColor, dayDirColor, changeTIme * 0.0005f);
	curSunColor = FMath::Lerp(curSunColor, daySunColor, changeTIme * 0.0005f);

	// directLight->SetLightColor(curDirColor);
	sun->SetLightColor(curSunColor);
	skyLight->SetLightColor(curDirColor);

	float changeParam = FMath::Lerp(0.0f, 4.0f, changeTIme * 0.04f);
	skySphere->SetScalarParameterValueOnMaterials(TEXT("Emissive_Power"), changeParam);
	
	dayParam.bOverride_BloomIntensity = true;
	dayParam.BloomIntensity  = 0.675f;
	levelPost->Settings = dayParam;

	if (changeTIme >= 10.1f)
	{
		isDay = false;
		changeTIme = 0;
		//skySphere->SetVisibility(false);

		SetState(ELightState::Stay);
	}
}

void ASJ_Actor_LevelLight::Night()
{
	changeTIme += GetWorld()->DeltaTimeSeconds;

	curDirColor = FMath::Lerp(curDirColor, nightDirColor, changeTIme * 0.0005f);
	curSunColor = FMath::Lerp(curSunColor, nightSunColor, changeTIme * 0.0005f);

	directLight->SetLightColor(curDirColor);
	sun->SetLightColor(curSunColor);

	if (changeTIme >= 10.1f)
	{
		isDay = false;
		changeTIme = 0;
		// skySphere->SetVisibility(true);

		SetState(ELightState::Stay);
	}
}

