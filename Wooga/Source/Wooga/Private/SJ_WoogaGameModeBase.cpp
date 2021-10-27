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
#include "SJ_HowToFireUIActor.h"
#include <Components/WidgetComponent.h>
#include "FirePosition.h"
#include "SJ_HowToFireNextUIActor.h"
#include "SJ_Actor_HowToManipulate.h"
#include "SJ_Actor_TitleUI.h"
#include "FireRock2.h"
#include "FireStraw.h"
#include "SJ_Actor_BreatheFireUI.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// �� ó�� ���� �߰� �������� ����
	SetState(EFlowState::InGame);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
}

#pragma region FlowStateFunction
void ASJ_WoogaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (flowState)
	{
	case EFlowState::InGame:
		InGame();
		break;
	case  EFlowState::ManipulateUI:
		ManipulateUI();
		break;
	case EFlowState::HowToGrabActorUI:
		GrabActorUI();
		break;
	case EFlowState::FireDiscoveryTitle:
		break;
	case EFlowState::HowToFireUI:
		HowToFireUI();
		break;
	case EFlowState::HowToFireUINext:
		HowToFireUINext();
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

void ASJ_WoogaGameModeBase::InGame()
{
	// ���� �� �ణ�� �����̸� �ְ� ����
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 5.0f)
	{
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// ���۹�� UI ����
		manipulateUI = GetWorld()->SpawnActor<ASJ_Actor_HowToManipulate>(bpManipulateUI, Param);

		nextDelayTime = 0;

		SetState(EFlowState::ManipulateUI);
	}
}

void ASJ_WoogaGameModeBase::ManipulateUI()
{
	if (player->isClose == true)
	{
		// ��¹�� UI ���� ����
		GetWorldTimerManager().SetTimer(howToGrabUITimer, this, &ASJ_WoogaGameModeBase::SpawnHowToGrabUI, 3.0f);

		SetState(EFlowState::HowToGrabActorUI);
	}
}

void ASJ_WoogaGameModeBase::GrabActorUI()
{
	// ��� ����� �˷��ִ� UI �� ������ ���� ������ �����Ѵ�.
	if (player->isClose == true)
	{
		bIsDelay = true;
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 3.0f)
			{
				// ������ ���� �ʱ�ȭ
				bIsDelay = false;
				nextDelayTime = 0;

				SpawnTitle();
				SetState(EFlowState::FireDiscoveryTitle);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::FireDiscoveryTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 9.0f)
	{
		// �ν˵� ĳ��
		fireRockOne = Cast<AFireRock>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock::StaticClass()));
		fireRockTwo = Cast<AFireRock2>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock2::StaticClass()));

		// �ν˵� �ƿ�����
		fireRockOne->outLine->SetVisibility(true);
		fireRockTwo->outLine->SetVisibility(true);

		// �Ҿ� UI ����
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		howToFire = GetWorld()->SpawnActor<ASJ_HowToFireUIActor>(howToFireUIActor, Param);

		SetState(EFlowState::HowToFireUI);
	}
}
#pragma endregion

#pragma region DiscoveryStateFunction


void ASJ_WoogaGameModeBase::HowToFireUI()
{
	firePosition = Cast<AFirePosition>(UGameplayStatics::GetActorOfClass(GetWorld(), AFirePosition::StaticClass()));

	fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (firePosition->bisFire == true)
	{
		// ��Ǫ���� ȭ�� �ƿ�����
		firePosition->outLine->SetVisibility(true);

		fireStraw->outLine->SetVisibility(true);
		
		//  �Ҿ� �ٴ����� �ű�� UI
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		howToFireNext = GetWorld()->SpawnActor<ASJ_HowToFireNextUIActor>(howToFireNextUIActor, Param);

		// �ӹ� �Ϸ� ����
		UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

		SetState(EFlowState::HowToFireUINext);
	}
}

void ASJ_WoogaGameModeBase::HowToFireUINext()
{
	// firePosition = Cast<AFirePosition>(UGameplayStatics::GetActorOfClass(GetWorld(), AFirePosition::StaticClass()));

	// fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (fireStraw->bisReadyFire == true)
	{
		// �ӹ� �Ϸ� ����
		UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		breatheFireUI = GetWorld()->SpawnActor<ASJ_Actor_BreatheFireUI>(bpBreatheFireUI, Param);
		SetState(EFlowState::Firing);
	}

	if (firePosition->bisFire == true)
	{
		// ���� UI ���ֱ�
		player->TurnOff();

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 2.0f)
		{
			// ������ ����ϴ� UI ����
			howToFire->Destroy();

			SetState(EFlowState::Firing);
			nextDelayTime = 0;
		}
	}
}

void ASJ_WoogaGameModeBase::Firing()
{
	// AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (fireStraw->isClear == false)
	{
		return;
	}

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

			// UI Sound
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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
		// �ð� ��ƽ ���
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		player->playerWatch->SetHiddenInGame(false);

		// �ӹ� �Ϸ� ����
		UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

		SetState(EFlowState::InformWatch);
	}
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// �ð� ���� UI ���� �� A ��ư���� ���� ���
	// UI�� ���� �̵� ����� �˷��ִ� UI ���� �� �̵� ���̵���� ����
	temporaryTime += GetWorld()->DeltaTimeSeconds;

	if (temporaryTime >= 5.0f)
	{
		guideLine = Cast<ASJ_GuidLine>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_GuidLine::StaticClass()));

		guideLine->SetActorHiddenInGame(false);
	}
}
void ASJ_WoogaGameModeBase::GoToCollectState()
{

}

void ASJ_WoogaGameModeBase::SpawnHowToGrabUI()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ���۽� ��� ��� �˷��ִ� UI ���� �ڵ�
	howToGrab = GetWorld()->SpawnActor<ASJ_HowToGrabUIActor>(howToGrabActor, Param);
}

void ASJ_WoogaGameModeBase::SpawnTitle()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ���� �߰� ����
	FDTitle = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpFDTitle, Param);

	// ������ ���� ���
}
#pragma endregion

#pragma region CollectStateFunction
void ASJ_WoogaGameModeBase::HowToCollectActorUI()
{
	if (player->isClose == true)
	{
		SetState(EFlowState::CollectAndEat);
	}
}

void ASJ_WoogaGameModeBase::CollectAndEat()
{
	// ä���Ͽ� ������ Ȧ�α׷� �����ϰ� ���� ���·� �Ѿ��

}

void ASJ_WoogaGameModeBase::CompleteCollect()
{
	// Ȧ�α׷� ����� ������ �÷��̾� ��ġ�� ���� 
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
}
#pragma endregion


