// Fill out your copyright notice in the Description page of Project Settings.


#include "LightIJ.h"

// Sets default values
ALightIJ::ALightIJ()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightIJ::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightIJ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (lightSource)
	{
		lightSource->AddActorLocalRotation(FRotator((DeltaTime * turnRate), 0, 0));
	}

	if (sun)
	{
		FOutputDeviceNull ar;
		sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}
}

