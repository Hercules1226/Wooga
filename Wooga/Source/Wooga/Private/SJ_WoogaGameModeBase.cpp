// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_WoogaGameModeBase.h"
#include "SJ_UIPannel.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireRock.h"
#include "FireStraw.h"
#include "SJ_Hologram.h"
#include "GrabActorComponent.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 맨 처음 불의 발견 교육으로 시작
	SetFlowState(EFlowState::FireDiscovery);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	GetWorldTimerManager().SetTimer(howToGrabOpenTIme, this, &ASJ_WoogaGameModeBase::OpenGrabUI, 3.0f);
}

void ASJ_WoogaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
#pragma region FlowStateMachine
	switch (flowState)
	{
	case EFlowState::FireDiscovery:
		break;
	case EFlowState::Collection:
		break;
	case EFlowState::FistAx:
		break;
	case EFlowState::FireUse:
		break;
	case EFlowState::Smelts:
		break;
	case EFlowState::DugoutHut:
		break;
	}
#pragma endregion

#pragma region DiscoveryStateMachine
	switch (discoveryState)
	{
	case EFireDiscoveryState::GrabActorUI:
		GrabActorUI();
		break;
	case EFireDiscoveryState::HowToFireUI:
		HowToFireUI();
		break;
	case EFireDiscoveryState::Firing:
		Firing();
		break;
	case EFireDiscoveryState::CompleteCourse:
		CompleteFireCourse();
		break;
	case EFireDiscoveryState::InformWatch:
		InformWatch();
		break;
	case EFireDiscoveryState::GoToNextStep:
		GoToCollectState();
		break;
	}

#pragma endregion

}

#pragma region FlowStateFunction
// 캡슐화
void ASJ_WoogaGameModeBase::SetFlowState(EFlowState state)
{
	flowState = state;
}

EFlowState ASJ_WoogaGameModeBase::GetFlowState()
{
	return EFlowState();
}

void ASJ_WoogaGameModeBase::FireDiscovery()
{
	SetDiscoveryState(EFireDiscoveryState::GrabActorUI);

}

void ASJ_WoogaGameModeBase::Collection()
{

}

void ASJ_WoogaGameModeBase::FistAx()
{

}

void ASJ_WoogaGameModeBase::FireUse()
{

}

void ASJ_WoogaGameModeBase::Smelts()
{

}

void ASJ_WoogaGameModeBase::DogoutHut()
{

}

#pragma endregion

#pragma region DiscoveryStateFunction
void ASJ_WoogaGameModeBase::SetDiscoveryState(EFireDiscoveryState state)
{
	discoveryState = state;
}
EFireDiscoveryState ASJ_WoogaGameModeBase::GetDiscoveryState()
{
	return EFireDiscoveryState();
}

void ASJ_WoogaGameModeBase::GrabActorUI()
{
	// 잡는 방법을 알려주는 UI 가 꺼지면 부싯돌을 잡는 상태로 넘어간다.
	if (player->isClose == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenHowToFireUI"));


		// UI 를 끄면 근처 아웃 라인이 켜지게
		TArray<AActor*> bpFireRocks;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFireRock::StaticClass(), bpFireRocks);

		for (int i = 0; i < bpFireRocks.Num(); i++)
		{
			AFireRock* emptyFireRock = nullptr;
			fireRocks.Add(emptyFireRock);
		}

		for (int i = 0; i < bpFireRocks.Num(); i++)
		{
			auto fr = Cast<AFireRock>(bpFireRocks[i]);
			fr->outLine->SetVisibility(true);
		}

		SetDiscoveryState(EFireDiscoveryState::HowToFireUI);
	}
}

void ASJ_WoogaGameModeBase::HowToFireUI()
{
	// 부싯돌을 두개 다 잡으면 불을 지필 수 있는 상태로 넘어간다.
	if (player->grabComp->fireRockR && player->grabComp->fireRockL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire"));

		// 불을 지필 수 있는 방법을 알려주는 UI
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		player->uiPannel = GetWorld()->SpawnActor<ASJ_UIPannel>(howToFireUIPannel, Param);

		SetDiscoveryState(EFireDiscoveryState::Firing);
	}
}

void ASJ_WoogaGameModeBase::Firing()
{
	AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	// 불을 켜면 홀로그램이 생성되고 첫번째 교육 이수 상태로 넘어간다.
	if (fireStraw->isClear == true)
	{
		// UI 꺼주기
		player->TurnOff();

		UE_LOG(LogTemp, Warning, TEXT("CompleteFireCourse"));
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		hologram = GetWorld()->SpawnActor<ASJ_Hologram>(fireDisCoveryHologram, Param);
		SetDiscoveryState(EFireDiscoveryState::CompleteCourse);
	}
}
void ASJ_WoogaGameModeBase::CompleteFireCourse()
{
	// 홀로그램이 꺼지면 시계로 들어가는 기능
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= destroyTime)
	{
		hologram->Destroy();

		// 시계 햅틱 기능
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		SetDiscoveryState(EFireDiscoveryState::InformWatch);
	}
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// 시계 위에 UI 생성 및 A 버튼으로 끄는 기능
	// UI를 끄면 이동 방법을 알려주는 UI 생성 및 이동 가이드라인 생성
}
void ASJ_WoogaGameModeBase::GoToCollectState()
{

}
#pragma endregion

void ASJ_WoogaGameModeBase::OpenGrabUI()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 시작시 잡는 방법 알려주는 UI 생성 코드
	player->uiPannel = GetWorld()->SpawnActor<ASJ_UIPannel>(howToGrab, Param);
}

void ASJ_WoogaGameModeBase::TurnOff()
{
	useUI->SetActorHiddenInGame(true);
}
