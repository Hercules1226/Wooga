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

	// �� ó�� ���� �߰� �������� ����
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
		FireDiscovery();
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
// ĸ��ȭ
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
	// ��� ����� �˷��ִ� UI �� ������ �ν˵��� ��� ���·� �Ѿ��.
	if (player->isClose == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenHowToFireUI"));
		player->uiPannel = nullptr;

		// UI �� ���� ��ó �ƿ� ������ ������
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
	// �ν˵��� �ΰ� �� ������ ���� ���� �� �ִ� ���·� �Ѿ��.
	if (player->grabComp->fireRockR && player->grabComp->fireRockL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire"));

		// ���� ���� �� �ִ� ����� �˷��ִ� UI
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		player->uiPannel = GetWorld()->SpawnActor<ASJ_UIPannel>(howToFireUIPannel, Param);

		SetDiscoveryState(EFireDiscoveryState::Firing);
	}
}

void ASJ_WoogaGameModeBase::Firing()
{
	AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	// ���� �Ѹ� Ȧ�α׷��� �����ǰ� ù��° ���� �̼� ���·� �Ѿ��.
	if (fireStraw->isClear == true)
	{
		// UI ���ֱ�
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
	// Ȧ�α׷��� ������ �ð�� ���� ���
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= destroyTime)
	{
		hologram->Destroy();

		// �ð� ��ƽ ���
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		SetDiscoveryState(EFireDiscoveryState::InformWatch);
	}
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// �ð� ���� UI ���� �� A ��ư���� ���� ���
	// UI�� ���� �̵� ����� �˷��ִ� UI ���� �� �̵� ���̵���� ����
}
void ASJ_WoogaGameModeBase::GoToCollectState()
{

}
#pragma endregion

void ASJ_WoogaGameModeBase::OpenGrabUI()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ���۽� ��� ��� �˷��ִ� UI ���� �ڵ�
	player->uiPannel = GetWorld()->SpawnActor<ASJ_UIPannel>(howToGrab, Param);
}

void ASJ_WoogaGameModeBase::TurnOff()
{
	useUI->SetActorHiddenInGame(true);
}
