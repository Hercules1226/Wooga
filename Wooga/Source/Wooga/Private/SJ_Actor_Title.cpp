	// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_Title.h"
#include <Components/StaticMeshComponent.h>
#include "SJ_WoogaGameModeBase.h"
#include <Kismet/GameplayStatics.h>

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

	// 제목 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), titleSound);

	// 게임모드 캐싱
	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameMode->flowState == EFlowState::HowToGrabActorUI || gameMode->flowState == EFlowState::FireDiscoveryTitle)
	{
		FVector p1 = FVector(10755, 11919, 1379);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 173, 0);

		SetActorRotation(r1);
	}
	// 채집하기
	else if (gameMode->flowState == EFlowState::GoToCollectCourse || gameMode->flowState == EFlowState::CollectTitle)
	{
		FVector p1 = FVector(9677, 10360, 1354);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 129, 0);

		SetActorRotation(r1);
	}
	// 주먹도끼 제목
	else if (gameMode->flowState == EFlowState::GoToFistAxCourse || gameMode->flowState == EFlowState::HandAxTitle)
	{
		FVector p2 = FVector(8286, 9116, 1304);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 140, 0);

		SetActorRotation(r2);
	}
	// 불의 활용
	else if (gameMode->flowState == EFlowState::GoToFireUse || gameMode->flowState == EFlowState::FireUseTitle)
	{
		FVector p3 = FVector(6302, 7470, 1302);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 121, 0);

		SetActorRotation(r3);
	}
	// 슴베찌르개
	else if (gameMode->flowState == EFlowState::GoToSpear || gameMode->flowState == EFlowState::SpearTitle)
	{
		FVector p4 = FVector(5096, 6803, 1302);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, -67, 0);

		SetActorRotation(r4);
	}
	// 움집
	else if (gameMode->flowState == EFlowState::GoToHut || gameMode->flowState == EFlowState::HutTitle)
	{
		FVector  p5 = FVector(4078, 7887, 1280);

		SetActorLocation(p5);

		FRotator  r5 = FRotator(0, 40, 0);

		SetActorRotation(r5);
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

	startParam = FMath::Lerp(1.0f, 0.0f, playTime);

	title->SetScalarParameterValueOnMaterials(TEXT("opacity"), startParam);

	if (playTime >= 2.0f)
	{
		playTime = 0;
		UGameplayStatics::PlaySound2D(GetWorld(), titleNarrationSound);
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

	endParam = FMath::Lerp(0.0f, 1.0f, playTime);

	title->SetScalarParameterValueOnMaterials(TEXT("opacity"), endParam);

	if (playTime >= 2.0f)
	{
		playTime = 0;
		Destroy();
	}
}

