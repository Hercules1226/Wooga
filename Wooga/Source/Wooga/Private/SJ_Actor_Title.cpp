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

	// ���� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), titleSound);

	// ���Ӹ�� ĳ��
	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameMode->flowState == EFlowState::HowToGrabActorUI || gameMode->flowState == EFlowState::FireDiscoveryTitle)
	{
		FVector p1 = FVector(10799, 12126, 1322);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 163, 0);

		SetActorRotation(r1);
	}
	// ä���ϱ�
	else if (gameMode->flowState == EFlowState::GoToCollectCourse || gameMode->flowState == EFlowState::CollectTitle)
	{
		FVector p1 = FVector(9636, 10356, 1301);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, 129, 0);

		SetActorRotation(r1);
	}
	// �ָԵ��� ����
	else if (gameMode->flowState == EFlowState::GoToFistAxCourse || gameMode->flowState == EFlowState::HandAxTitle)
	{
		FVector p2 = FVector(8182, 9219, 1301);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, 125, 0);

		SetActorRotation(r2);
	}
	// ���� Ȱ��
	else if (gameMode->flowState == EFlowState::GoToFireUse || gameMode->flowState == EFlowState::FireUseTitle)
	{
		FVector p3 = FVector(6364, 7232, 1301);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, 120, 0);

		SetActorRotation(r3);
	}
	// �������
	else if (gameMode->flowState == EFlowState::GoToSpear || gameMode->flowState == EFlowState::SpearTitle)
	{
		FVector p4 = FVector(5331, 6751, 1301);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, 130, 0);

		SetActorRotation(r4);
	}
	// ����
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

