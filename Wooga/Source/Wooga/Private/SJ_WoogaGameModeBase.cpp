// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_WoogaGameModeBase.h"
#include "SJ_UIPannel.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireRock.h"
#include "FireStraw.h"
#include "SJ_Hologram.h"
#include "GrabActorComponent.h"
#include "SJ_GuidLine.h"
#include "SJ_HowToGrabUIActor.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// �� ó�� ���� �߰� �������� ����
	SetState(EFlowState::HowToGrabActorUI);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	GetWorldTimerManager().SetTimer(howToGrabOpenTIme, this, &ASJ_WoogaGameModeBase::OpenGrabUI, 3.0f);
}

#pragma region FlowStateFunction
void ASJ_WoogaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (flowState)
	{
	case EFlowState::HowToGrabActorUI:
		GrabActorUI();
		break;
	case EFlowState::HowToFireUI:
		HowToFireUI();
		break;
	case EFlowState::Firing:
		Firing();
		break;
	case EFlowState::CompleteFireDiscovery:
		CompleteFireCourse();
		break;
	case EFlowState::InformWatch:
		InformWatch();
		break;
	case EFlowState::GoToCollectCourse:
		GoToCollectState();
		break;
	case EFlowState::HowToCollectActorUI:
		HowToCollectActorUI();
		break;
	case EFlowState::CollectAndEat:
		CollectAndEat();
		break;
	case EFlowState::CompleteCollect:
		CompleteCollect();
		break;
	case EFlowState::GoToFistAxCourse:
		GoToFistAxCourse();
		break;
	}
}

// ĸ��ȭ
void ASJ_WoogaGameModeBase::SetState(EFlowState state)
{
	flowState = state;
}

EFlowState ASJ_WoogaGameModeBase::GetState()
{
	return EFlowState();
}

#pragma endregion

#pragma region DiscoveryStateFunction
void ASJ_WoogaGameModeBase::GrabActorUI()
{
	// ��� ����� �˷��ִ� UI �� ������ �ν˵��� ��� ���·� �Ѿ��.
	if (player->isClose == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("OpenHowToFireUI"));

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

		SetState(EFlowState::HowToFireUI);
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

		SetState(EFlowState::Firing);
	}
}

void ASJ_WoogaGameModeBase::Firing()
{
	AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	// ���� �Ѹ� Ȧ�α׷��� �����ǰ� ù��° ���� �̼� ���·� �Ѿ��.
	if (fireStraw->isClear == true)
	{
		changeStateDelayTime += GetWorld()->DeltaTimeSeconds;
		if (changeStateDelayTime >= 3.0f)
		{
			// UI ���ֱ�
			player->TurnOff();

			UE_LOG(LogTemp, Warning, TEXT("CompleteFireCourse"));
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(fireDisCoveryHologram, Param);
			SetState(EFlowState::CompleteFireDiscovery);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteFireCourse()
{
	// Ȧ�α׷��� ������ �ð�� ���� ���
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= destroyTime)
	{
		// hologram->Destroy();

		// �ð� ��ƽ ���
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		SetState(EFlowState::InformWatch);
	}
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// �ð� ���� UI ���� �� A ��ư���� ���� ���
	// UI�� ���� �̵� ����� �˷��ִ� UI ���� �� �̵� ���̵���� ����
	temporaryTime += GetWorld()->DeltaTimeSeconds;

	if (temporaryTime >= 2.0f)
	{
		guideLine = Cast<ASJ_GuidLine>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_GuidLine::StaticClass()));

		guideLine->SetActorHiddenInGame(false);
	}

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
	howToGrab = GetWorld()->SpawnActor<ASJ_HowToGrabUIActor>(howToGrabActor, Param);
} 

#pragma region CollectStateFunction
void ASJ_WoogaGameModeBase::HowToCollectActorUI()
{
}

void ASJ_WoogaGameModeBase::CollectAndEat()
{
}

void ASJ_WoogaGameModeBase::CompleteCollect()
{
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
}
#pragma endregion


