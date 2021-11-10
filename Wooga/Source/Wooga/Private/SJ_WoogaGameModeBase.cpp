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
#include "SJ_InformUIPannel.h"
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

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// �� ó�� ���� �߰� �������� ����
	SetState(EFlowState::CompleteCollect);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
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
	case EFlowState::CollectTitle:
		CollectTitle();
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
	case  EFlowState::HandAxTitle:
		HandAxTitle();
		break;
	case EFlowState::SeeMammoth:
		SeeMammoth();
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
	case EFlowState::IndirectnessHit:
		break;
	case EFlowState::DirectlyHit:
		break;
	case  EFlowState::CompleteHandAx:
		break;
	}

	// UI ����
	if (bIsUIClose == true)
	{
		uiChange += DeltaSeconds;

		if (uiChange >= 0.1f)
		{
			bIsUIClose = false;
			uiChange = 0;
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
			titleUI = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpFDTitle, Param);

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
		// �ν˵� ĳ��
		fireRockOne = Cast<AFireRock>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock::StaticClass()));
		fireRockTwo = Cast<AFireRock2>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock2::StaticClass()));

		// �ν˵� �ƿ�����
		fireRockOne->outLine->SetVisibility(true);
		fireRockTwo->outLine->SetVisibility(true);

		// �Ҿ� UI ����
		howToFire = GetWorld()->SpawnActor<ASJ_HowToFireUIActor>(howToFireUIActor, Param);

		// ���� UI ����
		titleUI->Destroy();

		// �����̺��� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireUI);
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

		if (nextDelayTime >= 2.0f)
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

			// �ӹ� �Ϸ� ����
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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

		if (nextDelayTime >= 2.0f)
		{
			// �ӹ� �Ϸ� ����
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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
		firePosition->outLine->SetHiddenInGame(true);
		fireStraw->outLine->SetHiddenInGame(true);

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 3.0f)
		{
			// UI ���ֱ�
			bIsUIClose = true;

			// Ȧ�α׷� ����
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(fireDisCoveryHologram, Param);

			// UI Sound
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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

	if (nextDelayTime >= 20.0f)
	{
		// �ӹ� �Ϸ� ����
		UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		// ���� �ȳ� UI ����
		watchInformUI = GetWorld()->SpawnActor<ASJ_Actor_WatchInformUI>(bpWatchInformUI, Param);

		// ���� Ȧ�α׷� ����
		hologram->Destroy();

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
		informUI = GetWorld()->SpawnActor<ASJ_InformUIPannel>(bpGoToCollect, Param);

		watchInformUI->Destroy();

		// ������ ���� �ʱ�ȭ
		bIsDelay = false;
		nextDelayTime = 0;

		SetState(EFlowState::GoToCollectCourse);
	}
}

void ASJ_WoogaGameModeBase::GoToCollectState()
{
	// InformUIPannel ���� ����
	informUI = Cast<ASJ_InformUIPannel>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_InformUIPannel::StaticClass()));

	UDirectionalLightComponent* getLight = Cast<UDirectionalLightComponent>(directLight->GetComponentByClass(UDirectionalLightComponent::StaticClass()));

	getLight->SetLightColor(FVector(1.0f, 0.686685f, 0.181164f));

	if (informUI->isTrigger == true)
	{
		// ä���ϱ� ���� UI ����
		titleUI = GetWorld()->SpawnActor<class ASJ_Actor_TitleUI>(bpCollectTitleUI, Param);

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
		// ����İ� ä�� �ȳ� UI
		collectAndHungry = GetWorld()->SpawnActor<ASJ_Actor_CollectAndHungryUI>(bpCollectAndHungry, Param);

		// ���� ���ֱ�
		titleUI->Destroy();

		// �ӹ� �Ϸ� ����
		UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

		// �����̺��� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::HowToCollectActorUI);
	}
}
void ASJ_WoogaGameModeBase::HowToCollectActorUI()
{
	// UI�� ���� ���� ���·� �Ѿ��
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 3.0f)
		{
			// ��� ĳ���ϰ� �ƿ����� ���ֱ�
			apple = Cast<AApple>(UGameplayStatics::GetActorOfClass(GetWorld(), AApple::StaticClass()));

			apple->outLine->SetVisibility(true);

			// �ӹ� �Ϸ� ����
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

			// ��� ä���� �Ա� UI
			eatAppleUI = GetWorld()->SpawnActor<ASJ_Actor_EatAppleUI>(bpEatAppleUI, Param);

			// ��� UI ���ֱ�
			collectAndHungry->Destroy();

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

		if (nextDelayTime >= 3.0f)
		{
			// ä�� Ȧ�α׷� ����
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpCollectHologram, Param);

			// �ӹ� �Ϸ� ����
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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

	if (nextDelayTime >= 3.0f)
	{
		// �ƿ����� ����
		goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHandAxGuideLine, Param);

		nextDelayTime = 0;
		SetState(EFlowState::GoToFistAxCourse);
	}
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// �ָԵ���(����ϱ�) ���� ����
		titleUI = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpHandAxTitleUI, Param);

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
		// ���� ���ֱ�
		titleUI->Destroy();

		// ���̵���� ���ֱ�
		goToGuideLine->Destroy();

		// �����̺��� �ʱ�ȭ
		nextDelayTime = 0;

		// ���� ����
		mammothSpawn = GetWorld()->SpawnActor<ASJ_Actor_MammothSpawnDestroy>(bpMammothSpawn, Param);

		SetState(EFlowState::SeeMammoth);
	}
}
void ASJ_WoogaGameModeBase::SeeMammoth()
{
	// ī�޶� ����ũ�� ���� �÷���
	mammothShakeTime += GetWorld()->DeltaTimeSeconds;

	// 1�ʸ��� �ѹ��� ī�޶� ����ũ �÷���
	if (mammothShakeTime >= 1.0f)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(mammothCameraShake);

		mammothShakeTime = 0;
	}

	nextDelayTime += GetWorld()->DeltaTimeSeconds;
	
	if (nextDelayTime >= 15.0f)
	{
		// ���� ���� ���� ����
		mammothSpawn->Destroy();

		// �ָԵ��� �� ��� UI ����
		handAxUI = GetWorld()->SpawnActor<ASJ_Actor_GrabHandAxUI>(bpHandAxUI, Param);
		
		// �ָԵ��� �� �ƿ�����
		fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
		fistAxe->handHologramL->SetHiddenInGame(false);

		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::GrabHandAx);
	}
}

void ASJ_WoogaGameModeBase::GrabHandAx()
{
	if (player->grabComp->bisGrabFistAxeR == true)
	{
		// UI ����
		bIsUIClose = true;

		// ����� ����
		boar = GetWorld()->SpawnActor<ASJ_Character_Boar>(bpRunboar, Param);

		// ������ ���� �ʱ�ȭ
		nextDelayTime = 0;

		SetState(EFlowState::RunBoar);
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
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 3.0f)
		{
			// ���� UI ����
			hitBoarUI->Destroy();

			// �ָԵ��� ����� UI
			makeHandAxUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHandAxUI>(bpMakeHandAxUI, Param);

			// �ָԵ��� ������ ���� ��� �̵�
			goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpMakeHandAxGuideLine, Param);

			nextDelayTime = 0;

			SetState(EFlowState::MakeHandAx);
		}
	}
}
void ASJ_WoogaGameModeBase::MakeHandAx()
{
	if (goToGuideLine->isTrigger == true)
	{
		bIsUIClose = true;
		makeHandAxUI->Destroy();

		// �������� UI ����
		indirectUI = GetWorld()->SpawnActor<ASJ_Actor_IndirectHitUI>(bpIndirectUI, Param);

		SetState(EFlowState::IndirectnessHit);
	}
}
void ASJ_WoogaGameModeBase::IndirectHit()
{
	if (fistAxe->bisD1 == true)
	{
		// UI ���ֱ�
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 3.0f)
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

		if (nextDelayTime >= 3.0f)
		{
			// ��� UI ����
			directUI->Destroy();

			// �����̺��� �ʱ�ȭ
			nextDelayTime = 0;

			SetState(EFlowState::CompleteHandAx);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteHandAx()
{
}
#pragma endregion


