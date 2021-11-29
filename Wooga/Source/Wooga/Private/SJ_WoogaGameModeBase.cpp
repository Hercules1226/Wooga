// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_WoogaGameModeBase.h"
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
#include "SJ_Actor_BreatheFireUI.h"
#include "SJ_Actor_WatchInformUI.h"
#include "Apple.h"
#include "SJ_Actor_EatAppleUI.h"
#include "SJ_Actor_CollectAndHungryUI.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/LightComponent.h"
#include "SJ_Actor_GoToGuideLine.h"
#include "SJ_Actor_MammothSpawnDestroy.h"
#include "SJ_Character_Boar.h"
#include "SJ_Actor_GrabHandAxUI.h"
#include "SJ_Actor_HitBoarUI.h"
#include "SJ_Actor_MakeHandAxUI.h"
#include "FistAxe.h"
#include "SJ_Actor_IndirectHitUI.h"
#include "SJ_Actor_DirectHitUI.h"
#include "SJ_Actor_Hologram.h"
#include "SJ_Actor_CuttingPigUI.h"
#include "Engine/DirectionalLight.h"
#include "SJ_Actor_PickUpMeatUI.h"
#include "SJ_Actor_FireTwoUI.h"
#include "SlicePig.h"
#include "SliceMeat.h"
#include "Cutting.h"
#include "Cutting2.h"
#include "SJ_Actor_MakeRange.h"
#include "SJ_Actor_LevelLight.h"
#include "SJ_Actor_Title.h"
#include "Tomahowk.h"
#include "SJ_Actor_CookUI.h"
#include "SJ_Actor_EatMeatUI.h"
#include "SJ_Actor_GrabTomahowkUI.h"
#include "SJ_Actor_BreakStoneUI.h"
#include "SumjjiRock.h"
#include "SJ_Actor_ConnectSpearUI.h"
#include "Cable.h"
#include "SJ_Actor_TieSpearUI.h"
#include "String.h"
#include "SJ_Actor_HuntFishUI.h"
#include "SJ_Actor_CatchFish.h"
#include "SJ_Actor_CatchFishUI.h"
#include "SJ_Actor_GoFryFishUI.h"
#include "SJ_Actor_CookFishUI.h"
#include "SJ_Actor_EatFishUI.h"
#include "SJ_Actor_GoToHutUI.h"
#include "SJ_Actor_MakeHutUI.h"
#include "LastHouse.h"
#include "SJ_Actor_HowToFlow.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// �� ó�� ���� �߰� �������� ����
	SetState(EFlowState::SpawnHandAxGuideLine);

	// �׽�Ʈ�� ������Ʈ
	//SetState(EFlowState::CompleteCollect);

	// ���� �Ķ����
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// �÷��̾� ĳ����
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	// ���� ����
	slicePig = Cast<ASlicePig>(UGameplayStatics::GetActorOfClass(GetWorld(), ASlicePig::StaticClass()));
	slicePig->SetActorHiddenInGame(true);

	// ���� ����Ʈ 1
	cutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));
	cutting->SetActorHiddenInGame(true);

	// ���� ����Ʈ2
	// cuttingTwo = Cast<ACutting2>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting2::StaticClass()));
	// cuttingTwo->SetActorHiddenInGame(true);

	// �ڸ� ���
	// sliceMeat = Cast<ASliceMeat>(UGameplayStatics::GetActorOfClass(GetWorld(), ASliceMeat::StaticClass()));
	// sliceMeat->SetActorHiddenInGame(true);

	// �߸����
	tomahowk = Cast<ATomahowk>(UGameplayStatics::GetActorOfClass(GetWorld(), ATomahowk::StaticClass()));
	tomahowk->SetActorHiddenInGame(true);

	// ����Ʈ
	levelLight = Cast<ASJ_Actor_LevelLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_LevelLight::StaticClass()));
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
		FireDiscoveryTitle();
		break;
	case EFlowState::HowToFireDiscovery:
		HowToFIreDiscovery();
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
	case  EFlowState::SpawnCollectGuideLine:
		SpawnCollectGuideLine();
		break;
	case EFlowState::GoToCollectCourse:
		GoToCollectState();
		break;
	case EFlowState::CollectTitle:
		CollectTitle();
		break;
	case EFlowState::HowToCollect:
		HowToCollect();
		break;
	case EFlowState::CollectAndEat:
		CollectAndEat();
		break;
	case EFlowState::CompleteCollect:
		CompleteCollect();
		break;
	case EFlowState::SpawnHandAxGuideLine:
		SpawnHandAxGuideLine();
		break;
	case EFlowState::GoToFistAxCourse:
		GoToFistAxCourse();
		break;
	case  EFlowState::HandAxTitle:
		HandAxTitle();
		break;
	case EFlowState::HowToHunt:
		HowToHunt();
		break;
	case EFlowState::GrabHandAx:
		GrabHandAx();
		break;
	case  EFlowState::RunBoar:
		RunBoar();
		break;
	case EFlowState::HitBoar:
		HitBoar();
		break;
	case EFlowState::MakeHandAx:
		MakeHandAx();
		break;
	case EFlowState::HowToMakeHandAx:
		HowToMakeHandAx();
		break;
	case EFlowState::IndirectnessHit:
		IndirectHit();
		break;
	case EFlowState::DirectlyHit:
		DirectHit();
		break;
	case  EFlowState::CompleteHandAx:
		CompleteHandAx();
		break;
	case EFlowState::CuttingPig:
		CuttingPig();
		break;
	case EFlowState::GoToFireUse:
		GoToFireUse();
		break;
	case EFlowState::FireUseTitle:
		FireUseTitle();
		break;
	case EFlowState::HowToFireUse:
		HowToFireUse();
		break;
	case EFlowState::FiringTwo:
		FiringTwo();
		break;
	case EFlowState::CookMeat:
		CookMeat();
		break;
	case  EFlowState::EatMeat:
		EatMeat();
		break;
	case EFlowState::CompleteFireUse:
		CompleteFireUse();
		break;
	case EFlowState::GoToSpear:
		GoToSpear();
		break;
	case EFlowState::SpearTitle:
		SpearTitle();
		break;
	case EFlowState::MakeSpear:
		MakeSpear();
		break;
	case EFlowState::HowTomakeSpear:
		HowToMakeSpear();
		break;
	case EFlowState::TakeRock:
		TakeRock();
		break;
	case  EFlowState::ConnectSpear:
		ConnectSpear();
		break;
	case EFlowState::TieSpear:
		TieSpear();
		break;
	case EFlowState::CompleteSpear:
		CompleteSpear();
		break;
	case EFlowState::HuntFish:
		HuntFish();
		break;
	case EFlowState::CatchFish:
		CatchFish();
		break;
	case EFlowState::GoToCookFish:
		GoToCookFish();
		break;
	case EFlowState::CookFish:
		CookFish();
		break;
	case EFlowState::EatFish:
		EatFish();
		break;
	case  EFlowState::GoToHut:
		GoToHut();
		break;
	case EFlowState::HutTitle:
		HutTitle();
		break;
	case EFlowState::HowToMakeHut:
		HowToMakeHut();
		break;
	case EFlowState::MakeHut:
		MakeHut();
		break;
	case EFlowState::CompleteHut:
		CompleteHut();
		break;
	}

	// UI ����
	if (bIsUIClose == true)
	{
		isDelay = true;
	}

	if (isDelay == true)
	{
		uiChange += DeltaSeconds;

		if (uiChange >= 0.1f)
		{
			bIsUIClose = false;
		}

		if (uiChange >= 1.0f)
		{
			uiChange = 0;
			isDelay = false;
		}
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
		// ���۹�� UI ����
		manipulateUI = GetWorld()->SpawnActor<ASJ_Actor_HowToManipulate>(bpManipulateUI, Param);

		nextDelayTime = 0;

		SetState(EFlowState::ManipulateUI);
	}
}

void ASJ_WoogaGameModeBase::ManipulateUI()
{
	// ���� UI�� ����,
	if (player->isClose == true)
	{
		bIsDelay = true;
	}

	// �ð��� �帥��
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		// 3�� �ڿ� ���¸� ���� ���ش�.
		// ���Ŀ��� ���� ����� ����Ѵ�.
		if (nextDelayTime >= 3.0f)
		{
			// ���۽� ��� ��� �˷��ִ� UI ���� �ڵ�
			howToGrab = GetWorld()->SpawnActor<ASJ_HowToGrabUIActor>(howToGrabActor, Param);

			// ������ ���� �ʱ�ȭ
			bIsDelay = false;
			nextDelayTime = 0;

			// ���� UI ����
			manipulateUI->Destroy();

			SetState(EFlowState::HowToGrabActorUI);
		}
	}
}

void ASJ_WoogaGameModeBase::GrabActorUI()
{
	// ��� ����� �˷��ִ� UI �� ������ ���� ������ �����Ѵ�.
	if (player->isClose == true)
	{
		bIsDelay = true;
	}

	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 3.0f)
		{
			// ������ ���� �ʱ�ȭ
			bIsDelay = false;
			nextDelayTime = 0;

			// ���� UI ����
			howToGrab->Destroy();

			// ���� �߰� ����
			// titleUI = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpFDTitle, Param);
			title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpFDTitle, Param);

			SetState(EFlowState::FireDiscoveryTitle);
		}
	}
}
#pragma endregion

#pragma region DiscoveryStateFunction
void ASJ_WoogaGameModeBase::FireDiscoveryTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpFDHowToFlow, Param);

		// �����̺��� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireDiscovery);
	}
}

void ASJ_WoogaGameModeBase::HowToFIreDiscovery()
{
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// �ν˵� ĳ��
			fireRockOne = Cast<AFireRock>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock::StaticClass()));
			fireRockTwo = Cast<AFireRock2>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock2::StaticClass()));

			// �ν˵� �ƿ�����
			fireRockOne->outLine->SetVisibility(true);
			fireRockTwo->outLine->SetVisibility(true);

			// �Ҿ� UI ����
			howToFire = GetWorld()->SpawnActor<ASJ_HowToFireUIActor>(howToFireUIActor, Param);

			nextDelayTime = 0;

			SetState(EFlowState::HowToFireUI);
		}
	}
}

void ASJ_WoogaGameModeBase::HowToFireUI()
{
	// ��Ǫ���� ȭ�� ĳ��
	firePosition = Cast<AFirePosition>(UGameplayStatics::GetActorOfClass(GetWorld(), AFirePosition::StaticClass()));

	fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (firePosition->bisFire == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		// UI ���ֱ�
		bIsUIClose = true;

		if (nextDelayTime >= 1.0f)
		{
			// �ν˵� �ƿ����� ���ֱ�
			fireRockOne->outLine->SetHiddenInGame(true);
			fireRockTwo->outLine->SetHiddenInGame(true);

			// ��Ǫ���� ȭ�� �ƿ�����
			firePosition->outLine->SetVisibility(true);
			fireStraw->outLine->SetVisibility(true);

			//  �Ҿ� �ٴ����� �ű�� UI
			howToFireNext = GetWorld()->SpawnActor<ASJ_HowToFireNextUIActor>(howToFireNextUIActor, Param);

			// ���� UI ����
			howToFire->Destroy();

			nextDelayTime = 0;

			SetState(EFlowState::HowToFireUINext);
		}
	}
}

void ASJ_WoogaGameModeBase::HowToFireUINext()
{
	// firePosition = Cast<AFirePosition>(UGameplayStatics::GetActorOfClass(GetWorld(), AFirePosition::StaticClass()));

	// fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (fireStraw->bisReadyFire == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			breatheFireUI = GetWorld()->SpawnActor<ASJ_Actor_BreatheFireUI>(bpBreatheFireUI, Param);

			// ���� UI ����
			howToFireNext->Destroy();

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;
			SetState(EFlowState::Firing);
		}
	}
}

void ASJ_WoogaGameModeBase::Firing()
{
	// AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	// ���� �Ѹ� Ȧ�α׷��� �����ǰ� ù��° ���� �̼� ���·� �Ѿ��.
	if (fireStraw->isClear == true)
	{
		// ��Ǫ���� ȭ�� �ƿ�����
		// firePosition->outLine->SetHiddenInGame(true);
		fireStraw->outLine->SetHiddenInGame(true);

		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			// Ȧ�α׷� ����
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpFDHologram, Param);

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			// ���� UI ����
			breatheFireUI->Destroy();

			// �ð� ��ƽ ���
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			// �÷��̾� ��ġ ���ֱ�
			player->playerWatch->SetHiddenInGame(false);

			SetState(EFlowState::CompleteFireDiscovery);
		}
	}
}

void ASJ_WoogaGameModeBase::CompleteFireCourse()
{
	// Ȧ�α׷��� ������ �ð�� ���� ���
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 18.0f)
	{
		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		// ���� �ȳ� UI ����
		watchInformUI = GetWorld()->SpawnActor<ASJ_Actor_WatchInformUI>(bpWatchInformUI, Param);

		SetState(EFlowState::InformWatch);
	}
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// �ð� ���� UI ���� �� A ��ư���� ���� ���
	// UI�� ���� �̵� ����� �˷��ִ� UI ���� �� �̵� ���̵���� ����
	if (player->isClose == true)
	{
		bIsDelay = true;
	}

	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;
	}

	if (nextDelayTime >= 3.0f)
	{
		// ������ �� ���·� ����
		levelLight->isDay = true;

		watchInformUI->Destroy();

		// ������ ���� �ʱ�ȭ
		bIsDelay = false;
		nextDelayTime = 0;

		SetState(EFlowState::SpawnCollectGuideLine);
	}
}

void ASJ_WoogaGameModeBase::SpawnCollectGuideLine()
{
	// ���̵���� ����
	goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpCollectGuideLine, Param);

	SetState(EFlowState::GoToCollectCourse);
}

void ASJ_WoogaGameModeBase::GoToCollectState()
{
	if (goToGuideLine->isTrigger == true)
	{
		// ������ �ٽ� ����� �ֱ� ���� ����
		// fireStraw->Destroy();

		// ä���ϱ� ���� UI ����
		title = GetWorld()->SpawnActor<class ASJ_Actor_Title>(bpCollectTitle, Param);

		// ä�� ���·� �Ѿ��
		SetState(EFlowState::CollectTitle);
	}
}
#pragma endregion

#pragma region CollectStateFunction
void ASJ_WoogaGameModeBase::CollectTitle()
{
	// �̶� �̵��� ����
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ���̵���� ���ֱ�
		goToGuideLine->Destroy();

		// �����̺��� �ʱ�ȭ
		nextDelayTime = 0;

		// ä���ϱ� �ȳ� UI
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpCollectHowToFlow, Param);

		// ��� ĳ���ϰ� �ƿ����� ���ֱ�
		apple = Cast<AApple>(UGameplayStatics::GetActorOfClass(GetWorld(), AApple::StaticClass()));

		apple->outLine->SetVisibility(true);

		SetState(EFlowState::HowToCollect);
	}
}

void ASJ_WoogaGameModeBase::HowToCollect()
{
	// UI �� ����
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��� ä���� �Ա� UI
			eatAppleUI = GetWorld()->SpawnActor<ASJ_Actor_EatAppleUI>(bpEatAppleUI, Param);

			// �����̺��� �ʱ�ȭ
			bIsDelay = false;
			nextDelayTime = 0;

			SetState(EFlowState::CollectAndEat);
		}
	}
}

void ASJ_WoogaGameModeBase::CollectAndEat()
{
	// ä���Ͽ� ������ Ȧ�α׷� �����ϰ� ���� ���·� �Ѿ��
	if (apple->bisEatComplete == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		bIsUIClose = true;

		if (nextDelayTime >= 1.0f)
		{
			// ä�� Ȧ�α׷� ����
			hologram = GetWorld()->SpawnActor< ASJ_Hologram>(bpCollectHologram, Param);

			// ���� UI ����
			eatAppleUI->Destroy();
			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;
			SetState(EFlowState::CompleteCollect);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteCollect()
{
	// Ȧ�α׷� ����� ������ �÷��̾� ��ġ�� ���� 
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 15.0f)
	{
		nextDelayTime = 0;
		SetState(EFlowState::SpawnHandAxGuideLine);
	}
}

void ASJ_WoogaGameModeBase::SpawnHandAxGuideLine()
{
	// ���̵���� ����
	goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHandAxGuideLine, Param);

	SetState(EFlowState::GoToFistAxCourse);
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// �ָԵ���(����ϱ�) ���� ����
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpHandAxTitle, Param);

		SetState(EFlowState::HandAxTitle);
	}
}

#pragma endregion

#pragma region HandAxFunction
void ASJ_WoogaGameModeBase::HandAxTitle()
{
	// �̶� �̵��� ����
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ���̵���� ���ֱ�
		goToGuideLine->Destroy();

		// ��� �ϴ� �� ��ȯ
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToHunt, Param);

		// �����̺��� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::HowToHunt);
	}
}
void ASJ_WoogaGameModeBase::HowToHunt()
{
	// UI �� ����
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// �ָԵ��� �� ��� UI ����
			handAxUI = GetWorld()->SpawnActor<ASJ_Actor_GrabHandAxUI>(bpHandAxUI, Param);

			// �ָԵ��� �� �ƿ�����
			fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
			fistAxe->handHologramL->SetHiddenInGame(false);
			fistAxe->bisStartBreak = false;

			// �����̺��� �ʱ�ȭ
			bIsDelay = false;
			nextDelayTime = 0;

			SetState(EFlowState::GrabHandAx);
		}
	}
}

void ASJ_WoogaGameModeBase::GrabHandAx()
{
	if (player->grabComp->bisGrabFistAxeR == true)
	{
		// UI ����
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ����� ����
			boar = GetWorld()->SpawnActor<ASJ_Character_Boar>(bpRunboar, Param);

			// ���� ����
			mammothSpawn = GetWorld()->SpawnActor<ASJ_Actor_MammothSpawnDestroy>(bpMammothSpawn, Param);

			// ����� UI ����
			handAxUI->Destroy();

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			SetState(EFlowState::RunBoar);
		}
	}
}
void ASJ_WoogaGameModeBase::RunBoar()
{
	if (boar->boarState == EBoarState::SlowMotion)
	{
		// ����� ���� UI
		hitBoarUI = GetWorld()->SpawnActor<ASJ_Actor_HitBoarUI>(bpHitBoarUI, Param);

		SetState(EFlowState::HitBoar);
	}
}

void ASJ_WoogaGameModeBase::HitBoar()
{
	if (boar->boarState == EBoarState::Die)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			// ���� UI ����
			hitBoarUI->Destroy();

			howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeHandAx, Param);

			// ���ܵ״� ���� ������ ��ȯ
			slicePig->SetActorHiddenInGame(false);

			SetState(EFlowState::HowToMakeHandAx);
		}
	}
}

void ASJ_WoogaGameModeBase::HowToMakeHandAx()
{
	// UI �� ����
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{

		// �ָԵ��� ����� UI
		makeHandAxUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHandAxUI>(bpMakeHandAxUI, Param);

		// �ָԵ��� ������ ���� ��� �̵�
		makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

		// �����̺��� �ʱ�ȭ
		bIsDelay = false;
		nextDelayTime = 0;

		SetState(EFlowState::MakeHandAx);

	}
}

void ASJ_WoogaGameModeBase::MakeHandAx()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			makeHandAxUI->Destroy();

			// �������� UI ����
			indirectUI = GetWorld()->SpawnActor<ASJ_Actor_IndirectHitUI>(bpIndirectUI, Param);

			fistAxe->bisStartBreak = true;

			nextDelayTime = 0;

			SetState(EFlowState::IndirectnessHit);
		}
	}
}

void ASJ_WoogaGameModeBase::IndirectHit()
{
	if (fistAxe->bisD1 == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// �������� UI ���� 
			directUI = GetWorld()->SpawnActor<ASJ_Actor_DirectHitUI>(bpDirectHitUI, Param);

			// ��� UI ����
			indirectUI->Destroy();

			// �����̺��� �ʱ�ȭ
			nextDelayTime = 0;

			SetState(EFlowState::DirectlyHit);
		}
	}
}
void ASJ_WoogaGameModeBase::DirectHit()
{
	if (fistAxe->bisD15 == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;


		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			directUI->Destroy();

			// �����̺��� �ʱ�ȭ
			nextDelayTime = 0;

			// �ָԵ��� Ȧ�α׷� ����
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpHandAxHologram, Param);

			SetState(EFlowState::CompleteHandAx);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteHandAx()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 20.0f)
	{
		// ���� ���̵���� ����
		//goToGuideLine->Destroy();
		makeHandAxRange->Destroy();

		// ���� ���� UI ����
		cuttingPigUI = GetWorld()->SpawnActor<ASJ_Actor_CuttingPigUI>(bpCuttingPigUI, Param);

		cutting->SetActorHiddenInGame(false);
		//	cuttingTwo->SetActorHiddenInGame(false);
		// sliceMeat->SetActorHiddenInGame(false);

		//������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::CuttingPig);
	}
}
#pragma endregion

#pragma  region FireUse
void ASJ_WoogaGameModeBase::CuttingPig()
{
	// ���� ���� �Ϸ� ��� ������ �ִ� ����
	pigCutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));

	if (pigCutting->bisfinish == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		tomahowk->SetActorHiddenInGame(false);

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ���̵���� ����
			goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpFIreUseGuideLine, Param);

			slicePig->Destroy();
			// sliceMeat->Destroy();
			cutting->Destroy();
			// cuttingTwo->Destroy();

			// ��� ����� UI����
			pickUpMeatUI = GetWorld()->SpawnActor<ASJ_Actor_PickUpMeatUI>(bpPickUpMeatUI, Param);

			FVector fireStrawPosition = FVector(5173, 8000, 1177);
			FRotator fireStrawRotation = FRotator(0, 0, 0);

			// ���� ������ ������ ���̰� ���ۻ���
			fireStraw = GetWorld()->SpawnActor<AFireStraw>(bpFireStraw, fireStrawPosition, fireStrawRotation, Param);

			// ���ۿ� ���� �Ҿ� ������ ���� �������� �ϰ� �ϱ� ���� ���� ����
			fireStraw->bisReadyFire = true;
			fireStraw->bisOverlab = false;
			fireStraw->bisSmog = false;
			fireStraw->isClear = false;

			// ��� UI ����
			//6cuttingPigUI->Destroy();
			// ���� ����
			//makeHandAxRange->Destroy();

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			SetState(EFlowState::GoToFireUse);
		}
	}
}

void ASJ_WoogaGameModeBase::GoToFireUse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// ��� ����� UI ����
		pickUpMeatUI->Destroy();

		// ���� Ȱ�� UI ����
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpFireUseTitle, Param);

		SetState(EFlowState::FireUseTitle);
	}
}

void ASJ_WoogaGameModeBase::FireUseTitle()
{
	// �̶� �̵��� ����
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ���̵���� ���ֱ�
		//goToGuideLine->Destroy();

		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToFireUse, Param);

		// �����̺��� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireUse);
	}
}
void ASJ_WoogaGameModeBase::HowToFireUse()
{
	// UI �� ����
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ���� �Ҿ� �־��ּ��� UI ����
			fireTwoUI = GetWorld()->SpawnActor<ASJ_Actor_FireTwoUI>(bpFireTwoUI, Param);

			// �����̺��� �ʱ�ȭ
			bIsDelay = false;
			nextDelayTime = 0;

			SetState(EFlowState::FiringTwo);
		}
	}
}
void ASJ_WoogaGameModeBase::FiringTwo()
{
	if (fireStraw->isClear == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// �丮 UI ����
			cookUI = GetWorld()->SpawnActor<ASJ_Actor_CookUI>(bpCookUI, Param);
			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			// ��� UI �ı�
			fireTwoUI->Destroy();

			SetState(EFlowState::CookMeat);
		}
	}
}
void ASJ_WoogaGameModeBase::CookMeat()
{
	if (tomahowk->bisWelldone == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// �Ա� UI ����
			eatMeatUI = GetWorld()->SpawnActor<ASJ_Actor_EatMeatUI>(bpEatMeatUI, Param);
			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;
			// ��� UI �ı�
			cookUI->Destroy();

			SetState(EFlowState::EatMeat);
		}
	}
}
void ASJ_WoogaGameModeBase::EatMeat()
{
	if (tomahowk->bisBone == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// Ȧ�α׷� ���� 
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpFireUseHologram, Param);

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			// �Ա� UI ����
			eatMeatUI->Destroy();

			SetState(EFlowState::CompleteFireUse);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteFireUse()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 27.0f)
	{
		// ������� ���̵����
		goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpSpearGuideLine, Param);

		// ���� ��� �̵��Ͻÿ� UI
		grabTomahowk = GetWorld()->SpawnActor<ASJ_Actor_GrabTomahowkUI>(bpGrabTomahowkUI, Param);

		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::GoToSpear);
	}
}

void ASJ_WoogaGameModeBase::GoToSpear()
{
	if (goToGuideLine->isTrigger == true)
	{
		// ��� UI ����
		grabTomahowk->Destroy();
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpSpearTitle, Param);

		SetState(EFlowState::SpearTitle);
	}
}
#pragma  endregion

#pragma region SpearFunction
void ASJ_WoogaGameModeBase::SpearTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		// ���� ���� ����
		makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

		// goToGuideLine->Destroy();
		SetState(EFlowState::HowTomakeSpear);
	}
}

void ASJ_WoogaGameModeBase::HowToMakeSpear()
{
	// UI �� ����
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeSpear, Param);

			// �����̺��� �ʱ�ȭ
			bIsDelay = false;
			nextDelayTime = 0;

			SetState(EFlowState::MakeSpear);
		}
	}
}

void ASJ_WoogaGameModeBase::MakeSpear()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ������� 
			sumjjiRock = Cast<ASumjjiRock>(UGameplayStatics::GetActorOfClass(GetWorld(), ASumjjiRock::StaticClass()));
			sumjjiRock->outLine->SetVisibility(true);

			// ���� �̿��� �ٵ�������UI ����
			breakStoneUI = GetWorld()->SpawnActor<ASJ_Actor_BreakStoneUI>(bpBreakStoneUI, Param);

			// ������ ����
			nextDelayTime = 0;

			SetState(EFlowState::TakeRock);
		}
	}
}

// �� �ٵ��
void ASJ_WoogaGameModeBase::TakeRock()
{
	if (sumjjiRock->bisRockFin == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			breakStoneUI->Destroy();

			// ���� ���� UI ����
			connectSpearUI = GetWorld()->SpawnActor<ASJ_Actor_ConnectSpearUI>(bpConnectSpearUI, Param);

			cable = Cast<ACable>(UGameplayStatics::GetActorOfClass(GetWorld(), ACable::StaticClass()));
			// �ƿ����� ���ֱ�
			cable->outLine->SetVisibility(true);

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			SetState(EFlowState::ConnectSpear);
		}
	}
}

// ���� �����ϱ�
void ASJ_WoogaGameModeBase::ConnectSpear()
{
	if (cable->bIsConnect == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			connectSpearUI->Destroy();

			tieSpearUI = GetWorld()->SpawnActor<ASJ_Actor_TieSpearUI>(bpTieSpearUI, Param);

			string = Cast<AString>(UGameplayStatics::GetActorOfClass(GetWorld(), AString::StaticClass()));

			string->outLine->SetVisibility(true);

			nextDelayTime = 0;

			SetState(EFlowState::TieSpear);
		}
	}
}

// ���� ����
void ASJ_WoogaGameModeBase::TieSpear()
{
	if (cable->bIsTie == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			tieSpearUI->Destroy();

			makeHandAxRange->Destroy();

			// Ȧ�α׷� ����
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpSpearHologram, Param);

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			SetState(EFlowState::CompleteSpear);
		}
	}
}

void ASJ_WoogaGameModeBase::CompleteSpear()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 17.0f)
	{
		// ���� ����
		makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

		// ����� ��� UI
		huntFishUI = GetWorld()->SpawnActor<ASJ_Actor_HuntFishUI>(bpHuntFishUI, Param);

		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;
		SetState(EFlowState::HuntFish);
	}
}

void ASJ_WoogaGameModeBase::HuntFish()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			// huntFishUI->Destroy();
			huntFishUI->SetActorHiddenInGame(true);

			catchFishUI = GetWorld()->SpawnActor<ASJ_Actor_CatchFishUI>(bpCatchFishUI, Param);
			// ���� �����
			catchFish = Cast<ASJ_Actor_CatchFish>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_CatchFish::StaticClass()));
			catchFish->outlineFish->SetVisibility(true);

			// �����̺��� �ʱ�ȭ
			nextDelayTime = 0;
			SetState(EFlowState::CatchFish);
		}
	}
}

void ASJ_WoogaGameModeBase::CatchFish()
{
	if (catchFish->isAttacked == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			catchFish->Destroy();

			goFryFishUI = GetWorld()->SpawnActor<ASJ_Actor_GoFryFishUI>(bpGoFryFishUI, Param);
			makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpGoToFry, Param);

			// �����̺��� �ʱ�ȭ
			nextDelayTime = 0;
			SetState(EFlowState::GoToCookFish);
		}
	}
}
void ASJ_WoogaGameModeBase::GoToCookFish()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			goFryFishUI->Destroy();

			cookFishUI = GetWorld()->SpawnActor<ASJ_Actor_CookFishUI>(bpCookFishUI, Param);
			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;
			SetState(EFlowState::CookFish);
		}
	}
}
void ASJ_WoogaGameModeBase::CookFish()
{
	if (cable->bisWelldone == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			cookFishUI->Destroy();

			// ���� ����� �Ա� UI
			eatFishUI = GetWorld()->SpawnActor<ASJ_Actor_EatFishUI>(bpEatFishUI, Param);

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;
			SetState(EFlowState::EatFish);
		}

	}
}
void ASJ_WoogaGameModeBase::EatFish()
{
	if (cable->bisEat == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			// ��� UI ����
			eatFishUI->Destroy();

			// ���� ���̵����
			goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHutGuideLine, Param);

			// ���� ���̵���� UI
			goToHutUI = GetWorld()->SpawnActor<ASJ_Actor_GoToHutUI>(bpGoToHutUI, Param);

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;
			SetState(EFlowState::GoToHut);
		}
	}
}

#pragma  endregion

#pragma region HutFuntion
void ASJ_WoogaGameModeBase::GoToHut()
{
	if (goToGuideLine->isTrigger == true)
	{
		// ��� UI ����
		goToHutUI->Destroy();

		// ���� ����
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpHutTitle, Param);

		SetState(EFlowState::HutTitle);
	}
}
void ASJ_WoogaGameModeBase::HutTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ��������� UI ����
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeHut, Param);

		// ���̵���� ����
		goToGuideLine->Destroy();

		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::HowToMakeHut);
	}
}
void ASJ_WoogaGameModeBase::HowToMakeHut()
{
	// UI �� ����
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ��������� UI ����
			makeHutUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHutUI>(bpMakeHutUI, Param);

			// �����̺��� �ʱ�ȭ
			bIsDelay = false;
			nextDelayTime = 0;

			SetState(EFlowState::MakeHut);
		}
	}
}
void ASJ_WoogaGameModeBase::MakeHut()
{
	lastHouse = Cast<ALastHouse>(UGameplayStatics::GetActorOfClass(GetWorld(), ALastHouse::StaticClass()));

	if (lastHouse->bisClear)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 10.0f)
		{
			makeHutUI->Destroy();

			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpHutHologram, Param);

			// ������ ���� �ʱ�ȭ
			nextDelayTime = 0;

			SetState(EFlowState::CompleteHut);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteHut()
{
	// �÷���Ÿ�� 18�� ����Ÿ�� 22��
	UGameplayStatics::OpenLevel(this, TEXT("Outro"));
}

#pragma endregion

