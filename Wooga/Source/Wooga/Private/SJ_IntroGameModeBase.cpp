// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_IntroGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>

ASJ_IntroGameModeBase::ASJ_IntroGameModeBase()
{
	// PrimaryActorTick.bCanEverTick = true;
}

void ASJ_IntroGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(introSoundTimer, this, &ASJ_IntroGameModeBase::IntroSound, 3.0f, false);

	GetWorldTimerManager().SetTimer(moveLevelTimer, this, &ASJ_IntroGameModeBase::MoveLevel, 18.0f, false);

	GetWorldTimerManager().SetTimer(fadeOutTimer, this, &ASJ_IntroGameModeBase::FadeOutFunc, 15.0f, false);
}

void ASJ_IntroGameModeBase::IntroSound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), introNarration);
}

void ASJ_IntroGameModeBase::MoveLevel()
{
	UGameplayStatics::OpenLevel(this, TEXT("Dawn_cave3"));
}

void ASJ_IntroGameModeBase::FadeOutFunc()
{
	auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	cameraManager->StartCameraFade(0.f, 1.f, 2.5f, FLinearColor::Black, true, true);
}

