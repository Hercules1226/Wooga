// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_Title.h"
#include <Components/StaticMeshComponent.h>
#include "SJ_WoogaGameModeBase.h"

// Sets default values
ASJ_Actor_Title::ASJ_Actor_Title()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	title = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Title"));
	SetRootComponent(title);
}

// Called when the game starts or when spawned
void ASJ_Actor_Title::BeginPlay()
{
	Super::BeginPlay();

	// 게임모드 캐싱
	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameMode->flowState == EFlowState::HowToGrabActorUI || gameMode->flowState == EFlowState::FireDiscoveryTitle)
	{
		FVector p1 = FVector(10900, 11930, 1280);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 160, 0);

		SetActorRotation(r1);
	}


	SetState(ETitleState::On);
}

// Called every frame
void ASJ_Actor_Title::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (titleState)
	{
	case ETitleState::On:
		OnTitle();
		break;
	case ETitleState::Stay:
		StayTitle();
		break;
	case ETitleState::Off:
		OffTitle();
		break;
	}
}

ETitleState ASJ_Actor_Title::GetState()
{
	return ETitleState();
}

void ASJ_Actor_Title::SetState(ETitleState state)
{
	titleState = state;
}

void ASJ_Actor_Title::OnTitle()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	startParam = FMath::Lerp(0.0f, 1.0f, playTime);

	title->SetScalarParameterValueOnMaterials(TEXT("Opacity"), startParam);

	if (playTime >= 2.0f)
	{
		playTime = 0;
		SetState(ETitleState::Stay);
	}
}

void ASJ_Actor_Title::StayTitle()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	if (playTime >= 2.0f)
	{
		playTime = 0;
		SetState(ETitleState::Off);
	}
}

void ASJ_Actor_Title::OffTitle()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	endParam = FMath::Lerp(1.0f, 0.0f, playTime);

	title->SetScalarParameterValueOnMaterials(TEXT("Opacity"), endParam);

	if (playTime >= 2.0f)
	{
		playTime = 0;
		Destroy();
	}
}

