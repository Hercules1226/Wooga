// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_HowToFlow.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PostProcessComponent.h>
#include "SJ_WoogaGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"

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

void ASJ_Actor_HowToFlow::BeginPlay()
{
	Super::BeginPlay();
	
	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	// 불의 발견(불피우기) 방법
	if (gameMode->flowState == EFlowState::FireDiscoveryTitle)
	{
		FVector p1 = FVector(10900, 11920, 1290);
		SetActorLocation(p1);

		FRotator r1 = FRotator(0, -30, 0);
		SetActorRotation(r1);
	}
	// 채집하기 방법
	else if (gameMode->flowState == EFlowState::CollectTitle)
	{
		FVector p2 = FVector(9835, 10114, 1300);
		SetActorLocation(p2);

		FRotator r2 = FRotator(0, -30, 0);
		SetActorRotation(r2);
	}
	// 사냥하기 방법
	else if (gameMode->flowState == EFlowState::HandAxTitle)
	{
		FVector p3 = FVector(8006, 8907, 1295);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, -40, 0);

		SetActorRotation(r3);
	}
	else if (gameMode->flowState == EFlowState::HitBoar)
	{
		FVector p4 = FVector(7524, 8777, 1290);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, -130, 0);

		SetActorRotation(r4);
	}
	else if (gameMode->flowState == EFlowState::FireUseTitle)
	{
		FVector p5 = FVector(5177, 7877, 1300);

		SetActorLocation(p5);

		FRotator r5 = FRotator(0, -140, 0);

		SetActorRotation(r5);
	}
	else if (gameMode->flowState == EFlowState::SpearTitle)
	{
		FVector p6 = FVector(4151, 6680, 1320);

		SetActorLocation(p6);

		FRotator r6 = FRotator(0, -20, 0);

		SetActorRotation(r6);
	}
	else if (gameMode->flowState == EFlowState::HutTitle)
	{
		FVector p7 = FVector(4186, 8070, 1300);

		SetActorLocation(p7);

		FRotator r7 = FRotator(0, -110, 0);

		SetActorRotation(r7);
	}

	SetState(ESaturateState::OnSature);

	/*
	startParam.bOverride_ColorSaturation = true;
	startParam.ColorSaturation = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
	howToPost->Settings = startParam;
	*/
	
	howToPlane->SetRenderCustomDepth(true);
}

void ASJ_Actor_HowToFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (saturateState)
	{
	case ESaturateState::OnSature:
		OnSature();
		break;
	case ESaturateState::Stay:
		Stay();
		break;
	case ESaturateState::OffSature:
		OffSature();
		break;
	}
}

ESaturateState ASJ_Actor_HowToFlow::GetState()
{
	return ESaturateState();
}

void ASJ_Actor_HowToFlow::SetState(ESaturateState state)
{
	saturateState = state;
}

void ASJ_Actor_HowToFlow::OnSature()
{
	onTime += GetWorld()->DeltaTimeSeconds;

	startDissolveParam = FMath::Lerp(-1.0f, 1.0f, onTime);

	howToPlane->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), startDissolveParam);

	// 포스트프로세스 흑백 조절
	/*
	float satValue = FMath::Lerp(1.0f, 0.4f, onTime);
	onParam.bOverride_ColorSaturation = true;
	onParam.ColorSaturation = FVector4(1.0f, 1.0f, 1.0f, satValue);
	howToPost->Settings = onParam;
	*/

	if (onTime >= 1.0f)
	{
		onTime = 0;
		SetState(ESaturateState::Stay);
	}
}

void ASJ_Actor_HowToFlow::Stay()
{
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	if (player->isClose)
	{
		SetState(ESaturateState::OffSature);
	}
}

void ASJ_Actor_HowToFlow::OffSature()
{
	offTime += GetWorld()->DeltaTimeSeconds;

	endDissolveParam = FMath::Lerp(1.0f, -1.0f, offTime);

	howToPlane->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), endDissolveParam);

	// 포스트 흑백 조절
	/*
	float offValue = FMath::Lerp(0.4f, 1.0f, offTime);
	offParam.bOverride_ColorSaturation = true;
	offParam.ColorSaturation = FVector4(1.0f, 1.0f, 1.0f, offValue);
	howToPost->Settings = offParam;
	*/

	if (offTime >= 1.0f)
	{
		offTime = 0;
		SetState(ESaturateState::OnSature);
		Destroy();
	}
}

