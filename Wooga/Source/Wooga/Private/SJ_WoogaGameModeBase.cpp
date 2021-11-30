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
#include "SJ_Actor_MakeSpearUI.h"
#include "Stick.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 맨 처음 불의 발견 교육으로 시작
	SetState(EFlowState::InGame);

	// 테스트용 스테이트
	//SetState(EFlowState::CompleteCollect);

	// 스폰 파라미터
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 플레이어 캐스팅
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	// 죽은 돼지
	slicePig = Cast<ASlicePig>(UGameplayStatics::GetActorOfClass(GetWorld(), ASlicePig::StaticClass()));
	slicePig->SetActorHiddenInGame(true);

	// 정육 포인트 1
	cutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));
	cutting->SetActorHiddenInGame(true);

	// 정육 포인트2
	// cuttingTwo = Cast<ACutting2>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting2::StaticClass()));
	// cuttingTwo->SetActorHiddenInGame(true);

	// 자를 고기
	// sliceMeat = Cast<ASliceMeat>(UGameplayStatics::GetActorOfClass(GetWorld(), ASliceMeat::StaticClass()));
	// sliceMeat->SetActorHiddenInGame(true);

	// 잘린고기
	tomahowk = Cast<ATomahowk>(UGameplayStatics::GetActorOfClass(GetWorld(), ATomahowk::StaticClass()));
	tomahowk->SetActorHiddenInGame(true);

	// 움집
	lastHouse = Cast<ALastHouse>(UGameplayStatics::GetActorOfClass(GetWorld(), ALastHouse::StaticClass()));
	lastHouse->SetActorHiddenInGame(true);

	// 라이트
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

	// UI 로직
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

// 캡슐화
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
	// 시작 시 약간의 딜레이를 주고 시작
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 5.0f)
	{
		// 조작방법 UI 생성
		manipulateUI = GetWorld()->SpawnActor<ASJ_Actor_HowToManipulate>(bpManipulateUI, Param);

		nextDelayTime = 0;

		SetState(EFlowState::ManipulateUI);
	}
}

void ASJ_WoogaGameModeBase::ManipulateUI()
{
	// 만약 UI를 끄면,
	if (player->isClose == true)
	{
		bIsDelay = true;
	}

	// 시간이 흐른다
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		// 3초 뒤에 상태를 변경 해준다.
		// 이후에도 같은 방법을 사용한다.
		if (nextDelayTime >= 3.0f)
		{
			// 시작시 잡는 방법 알려주는 UI 생성 코드
			howToGrab = GetWorld()->SpawnActor<ASJ_HowToGrabUIActor>(howToGrabActor, Param);

			// 딜레이 변수 초기화
			bIsDelay = false;
			nextDelayTime = 0;

			// 사용된 UI 제거
			manipulateUI->Destroy();

			SetState(EFlowState::HowToGrabActorUI);
		}
	}
}

void ASJ_WoogaGameModeBase::GrabActorUI()
{
	// 잡는 방법을 알려주는 UI 가 꺼지면 교육 제목을 생성한다.
	if (player->isClose == true)
	{
		bIsDelay = true;
	}

	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 3.0f)
		{
			// 딜레이 변수 초기화
			bIsDelay = false;
			nextDelayTime = 0;

			// 사용된 UI 제거
			howToGrab->Destroy();

			// 불의 발견 제목
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

		// 딜레이변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireDiscovery);
	}
}

void ASJ_WoogaGameModeBase::HowToFIreDiscovery()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 15.0f)
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
				// 부싯돌 캐싱
				fireRockOne = Cast<AFireRock>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock::StaticClass()));
				fireRockTwo = Cast<AFireRock2>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock2::StaticClass()));

				// 부싯돌 아웃라인
				fireRockOne->outLine->SetVisibility(true);
				fireRockTwo->outLine->SetVisibility(true);

				// 불씨 UI 생성
				howToFire = GetWorld()->SpawnActor<ASJ_HowToFireUIActor>(howToFireUIActor, Param);

				howToNarTime = 0;
				nextDelayTime = 0;

				SetState(EFlowState::HowToFireUI);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::HowToFireUI()
{
	// 지푸라기와 화로 캐싱
	firePosition = Cast<AFirePosition>(UGameplayStatics::GetActorOfClass(GetWorld(), AFirePosition::StaticClass()));

	fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (firePosition->bisFire == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		// UI 꺼주기
		bIsUIClose = true;

		if (nextDelayTime >= 1.0f)
		{
			// 부싯돌 아웃라인 꺼주기
			fireRockOne->outLine->SetHiddenInGame(true);
			fireRockTwo->outLine->SetHiddenInGame(true);

			// 지푸라기와 화로 아웃라인
			firePosition->outLine->SetVisibility(true);
			fireStraw->outLine->SetVisibility(true);

			//  불씨 바닥으로 옮기는 UI
			howToFireNext = GetWorld()->SpawnActor<ASJ_HowToFireNextUIActor>(howToFireNextUIActor, Param);

			// 사용된 UI 제거
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
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			breatheFireUI = GetWorld()->SpawnActor<ASJ_Actor_BreatheFireUI>(bpBreatheFireUI, Param);

			// 사용된 UI 제거
			howToFireNext->Destroy();

			// 딜레이 변수 초기화
			nextDelayTime = 0;
			SetState(EFlowState::Firing);
		}
	}
}

void ASJ_WoogaGameModeBase::Firing()
{
	// AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	// 불을 켜면 홀로그램이 생성되고 첫번째 교육 이수 상태로 넘어간다.
	if (fireStraw->isClear == true)
	{
		// 지푸라기와 화로 아웃라인
		// firePosition->outLine->SetHiddenInGame(true);
		fireStraw->outLine->SetHiddenInGame(true);

		// 사용된 UI 제거
		breatheFireUI->Destroy();

		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 3.0f)
		{
			// 홀로그램 생성
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpFDHologram, Param);

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			// 시계 햅틱 기능
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			// 플레이어 워치 켜주기
			player->playerWatch->SetHiddenInGame(false);

			SetState(EFlowState::CompleteFireDiscovery);
		}
	}
}

void ASJ_WoogaGameModeBase::CompleteFireCourse()
{
	// 홀로그램이 꺼지면 시계로 들어가는 기능
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 18.0f)
	{
		// 딜레이 변수 초기화
		nextDelayTime = 0;

		// 지식 안내 UI 생성
		watchInformUI = GetWorld()->SpawnActor<ASJ_Actor_WatchInformUI>(bpWatchInformUI, Param);

		SetState(EFlowState::InformWatch);
	}
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// 시계 위에 UI 생성 및 A 버튼으로 끄는 기능
	// UI를 끄면 이동 방법을 알려주는 UI 생성 및 이동 가이드라인 생성
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
		// 라이팅 낮 상태로 변경
		levelLight->isDay = true;

		watchInformUI->Destroy();

		// 딜레이 변수 초기화
		bIsDelay = false;
		nextDelayTime = 0;

		SetState(EFlowState::SpawnCollectGuideLine);
	}
}

void ASJ_WoogaGameModeBase::SpawnCollectGuideLine()
{
	// 가이드라인 생성
	goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpCollectGuideLine, Param);

	SetState(EFlowState::GoToCollectCourse);
}

void ASJ_WoogaGameModeBase::GoToCollectState()
{
	if (goToGuideLine->isTrigger == true)
	{
		// 장작을 다시 사용해 주기 위한 세팅
		// fireStraw->Destroy();

		// 채집하기 제목 UI 생성
		title = GetWorld()->SpawnActor<class ASJ_Actor_Title>(bpCollectTitle, Param);

		// 채집 상태로 넘어가기
		SetState(EFlowState::CollectTitle);
	}
}
#pragma endregion

#pragma region CollectStateFunction
void ASJ_WoogaGameModeBase::CollectTitle()
{
	// 이때 이동을 막자
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// 가이드라인 없애기
		goToGuideLine->Destroy();

		// 딜레이변수 초기화
		nextDelayTime = 0;

		// 채집하기 안내 UI
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpCollectHowToFlow, Param);

		// 사과 캐싱하고 아웃라인 켜주기
		apple = Cast<AApple>(UGameplayStatics::GetActorOfClass(GetWorld(), AApple::StaticClass()));

		apple->outLine->SetVisibility(true);

		SetState(EFlowState::HowToCollect);
	}
}

void ASJ_WoogaGameModeBase::HowToCollect()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 4.0f)
	{
		// UI 를 끄면
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// 사과 채집과 먹기 UI
				eatAppleUI = GetWorld()->SpawnActor<ASJ_Actor_EatAppleUI>(bpEatAppleUI, Param);

				// 딜레이변수 초기화
				bIsDelay = false;
				howToNarTime = 0;
				nextDelayTime = 0;

				SetState(EFlowState::CollectAndEat);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::CollectAndEat()
{
	// 채집하여 먹으면 홀로그램 생성하고 다음 상태로 넘어가기
	if (apple->bisEatComplete == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		bIsUIClose = true;

		if (nextDelayTime >= 1.0f)
		{
			// 채집 홀로그램 생성
			hologram = GetWorld()->SpawnActor< ASJ_Hologram>(bpCollectHologram, Param);

			// 사용된 UI 삭제
			eatAppleUI->Destroy();
			// 딜레이 변수 초기화
			nextDelayTime = 0;
			SetState(EFlowState::CompleteCollect);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteCollect()
{
	// 홀로그램 재생이 끝나면 플레이어 워치로 들어가고 
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 15.0f)
	{
		nextDelayTime = 0;
		SetState(EFlowState::SpawnHandAxGuideLine);
	}
}

void ASJ_WoogaGameModeBase::SpawnHandAxGuideLine()
{
	// 가이드라인 생성
	goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHandAxGuideLine, Param);

	SetState(EFlowState::GoToFistAxCourse);
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// 주먹도끼(사냥하기) 제목 생성
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpHandAxTitle, Param);

		SetState(EFlowState::HandAxTitle);
	}
}

#pragma endregion

#pragma region HandAxFunction
void ASJ_WoogaGameModeBase::HandAxTitle()
{
	// 이때 이동을 막자
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// 가이드라인 없애기
		goToGuideLine->Destroy();

		// 사냥 하는 법 소환
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToHunt, Param);

		// 딜레이변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::HowToHunt);
	}
}
void ASJ_WoogaGameModeBase::HowToHunt()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 9.0f)
	{
		// UI 를 끄면
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// 주먹도끼 돌 잡기 UI 생성
				handAxUI = GetWorld()->SpawnActor<ASJ_Actor_GrabHandAxUI>(bpHandAxUI, Param);

				// 주먹도끼 돌 아웃라인
				fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
				fistAxe->handHologramL->SetHiddenInGame(false);
				fistAxe->bisStartBreak = false;

				// 딜레이변수 초기화
				bIsDelay = false;

				howToNarTime = 0;
				nextDelayTime = 0;

				SetState(EFlowState::GrabHandAx);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::GrabHandAx()
{
	if (player->grabComp->bisGrabFistAxeR == true)
	{
		// UI 끄기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 멧돼지 생성
			boar = GetWorld()->SpawnActor<ASJ_Character_Boar>(bpRunboar, Param);

			// 맘모스 생성
			mammothSpawn = GetWorld()->SpawnActor<ASJ_Actor_MammothSpawnDestroy>(bpMammothSpawn, Param);

			// 돌잡기 UI 제거
			handAxUI->Destroy();

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			SetState(EFlowState::RunBoar);
		}
	}
}
void ASJ_WoogaGameModeBase::RunBoar()
{
	if (boar->boarState == EBoarState::SlowMotion)
	{
		// 멧돼지 가격 UI
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
			// 사용된 UI 제거
			hitBoarUI->Destroy();

			// 주먹도끼 만들기 UI
			makeHandAxUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHandAxUI>(bpMakeHandAxUI, Param);

			// 주먹도끼 제작을 위한 장소 이동
			makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

			// 숨겨뒀던 죽은 돼지를 소환
			slicePig->SetActorHiddenInGame(false);

			SetState(EFlowState::MakeHandAx);
		}
	}
}

void ASJ_WoogaGameModeBase::MakeHandAx()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			makeHandAxUI->Destroy();

			howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeHandAx, Param);

			nextDelayTime = 0;

			SetState(EFlowState::HowToMakeHandAx);
		}
	}
}

void ASJ_WoogaGameModeBase::HowToMakeHandAx()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 9.0f)
	{
		// UI 를 끄면
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			// 간접떼기 UI 생성
			indirectUI = GetWorld()->SpawnActor<ASJ_Actor_IndirectHitUI>(bpIndirectUI, Param);

			// 타격 포인트
			GetWorld()->SpawnActor<AActor>(bpHitPoint, FVector(7700, 8880, 1230), FRotator(0, 0, 0), Param);

			fistAxe->bisStartBreak = true;

			// 딜레이변수 초기화
			bIsDelay = false;

			nextDelayTime = 0;
			howToNarTime = 0;

			SetState(EFlowState::IndirectnessHit);

		}
	}
}

void ASJ_WoogaGameModeBase::IndirectHit()
{
	if (fistAxe->bisD1 == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 직접떼기 UI 생성 
			directUI = GetWorld()->SpawnActor<ASJ_Actor_DirectHitUI>(bpDirectHitUI, Param);

			// 사용 UI 제거
			indirectUI->Destroy();

			// 딜레이변수 초기화
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
			// 사용 UI 제거
			directUI->Destroy();

			// 딜레이변수 초기화
			nextDelayTime = 0;

			// 주먹도끼 홀로그램 생성
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
		// 간이 가이드라인 제거
		//goToGuideLine->Destroy();
		makeHandAxRange->Destroy();

		// 돼지 정육 UI 생성
		cuttingPigUI = GetWorld()->SpawnActor<ASJ_Actor_CuttingPigUI>(bpCuttingPigUI, Param);

		cutting->SetActorHiddenInGame(false);
		//	cuttingTwo->SetActorHiddenInGame(false);
		// sliceMeat->SetActorHiddenInGame(false);

		//딜레이 변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::CuttingPig);
	}
}
#pragma endregion

#pragma  region FireUse
void ASJ_WoogaGameModeBase::CuttingPig()
{
	// 돼지 정육 완료 기능 가지고 있는 액터
	pigCutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));

	if (pigCutting->bisfinish == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		tomahowk->SetActorHiddenInGame(false);

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 가이드라인 생성
			goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpFIreUseGuideLine, Param);

			slicePig->Destroy();
			// sliceMeat->Destroy();
			cutting->Destroy();
			// cuttingTwo->Destroy();

			// 고기 들고가기 UI생성
			pickUpMeatUI = GetWorld()->SpawnActor<ASJ_Actor_PickUpMeatUI>(bpPickUpMeatUI, Param);

			FVector fireStrawPosition = FVector(5173, 8000, 1177);
			FRotator fireStrawRotation = FRotator(0, 0, 0);

			// 도착 했을때 장작이 보이게 장작생성
			fireStraw = GetWorld()->SpawnActor<AFireStraw>(bpFireStraw, fireStrawPosition, fireStrawRotation, Param);

			// 장작에 숨만 불어 넣으면 불이 켜지도록 하게 하기 위한 변수 세팅
			fireStraw->bisReadyFire = true;
			fireStraw->bisOverlab = false;
			fireStraw->bisSmog = false;
			fireStraw->isClear = false;

			// 사용 UI 제거
			//6cuttingPigUI->Destroy();
			// 발판 제거
			//makeHandAxRange->Destroy();

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			SetState(EFlowState::GoToFireUse);
		}
	}
}

void ASJ_WoogaGameModeBase::GoToFireUse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// 고기 들고가기 UI 제거
		pickUpMeatUI->Destroy();

		// 불의 활용 UI 생성
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpFireUseTitle, Param);

		SetState(EFlowState::FireUseTitle);
	}
}

void ASJ_WoogaGameModeBase::FireUseTitle()
{
	// 이때 이동을 막자
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// 가이드라인 없애기
		goToGuideLine->Destroy();

		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToFireUse, Param);

		// 딜레이변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireUse);
	}
}
void ASJ_WoogaGameModeBase::HowToFireUse()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 10.0f)
	{
		// UI 를 끄면
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				fireStraw->outLine->SetVisibility(true);
				// 숨을 불어 넣어주세요 UI 생성
				fireTwoUI = GetWorld()->SpawnActor<ASJ_Actor_FireTwoUI>(bpFireTwoUI, Param);

				// 딜레이변수 초기화
				bIsDelay = false;
				nextDelayTime = 0;
				howToNarTime = 0;

				SetState(EFlowState::FiringTwo);
			}
		}
	}
}
void ASJ_WoogaGameModeBase::FiringTwo()
{
	if (fireStraw->isClear == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 요리 UI 생성
			cookUI = GetWorld()->SpawnActor<ASJ_Actor_CookUI>(bpCookUI, Param);
			// 딜레이 변수 초기화
			nextDelayTime = 0;

			// 사용 UI 파괴
			fireTwoUI->Destroy();

			SetState(EFlowState::CookMeat);
		}
	}
}
void ASJ_WoogaGameModeBase::CookMeat()
{
	if (tomahowk->bisWelldone == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 먹기 UI 생성
			eatMeatUI = GetWorld()->SpawnActor<ASJ_Actor_EatMeatUI>(bpEatMeatUI, Param);
			// 딜레이 변수 초기화
			nextDelayTime = 0;
			// 사용 UI 파괴
			cookUI->Destroy();

			SetState(EFlowState::EatMeat);
		}
	}
}
void ASJ_WoogaGameModeBase::EatMeat()
{
	if (tomahowk->bisBone == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 홀로그램 생성 
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpFireUseHologram, Param);

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			// 먹기 UI 제거
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
		// 슴베찌르개 가이드라인
		goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpSpearGuideLine, Param);

		// 뼈를 들고 이동하시오 UI
		grabTomahowk = GetWorld()->SpawnActor<ASJ_Actor_GrabTomahowkUI>(bpGrabTomahowkUI, Param);

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::GoToSpear);
	}
}

void ASJ_WoogaGameModeBase::GoToSpear()
{
	if (goToGuideLine->isTrigger == true)
	{
		// 사용 UI 제거
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
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeSpear, Param);

		goToGuideLine->Destroy();

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		// goToGuideLine->Destroy();
		SetState(EFlowState::HowTomakeSpear);
	}
}

void ASJ_WoogaGameModeBase::HowToMakeSpear()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 14.0f)
	{
		// UI 를 끄면
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// 제작 범위 생성
				makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

				// 슴베찌르개 제작 UI
				makeSpearUI = GetWorld()->SpawnActor<ASJ_Actor_MakeSpearUI>(bpMakeSpearUI, Param);

				// 딜레이변수 초기화
				bIsDelay = false;
				nextDelayTime = 0;
				howToNarTime = 0;

				SetState(EFlowState::MakeSpear);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::MakeSpear()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 슴베찌르개 
			sumjjiRock = Cast<ASumjjiRock>(UGameplayStatics::GetActorOfClass(GetWorld(), ASumjjiRock::StaticClass()));
			sumjjiRock->outLine->SetVisibility(true);

			makeSpearUI->Destroy();

			// 뼈를 이용해 다듬으세요UI 생성
			breakStoneUI = GetWorld()->SpawnActor<ASJ_Actor_BreakStoneUI>(bpBreakStoneUI, Param);

			// 딜레이 변수
			nextDelayTime = 0;

			SetState(EFlowState::TakeRock);
		}
	}
}

// 돌 다듬기
void ASJ_WoogaGameModeBase::TakeRock()
{
	if (sumjjiRock->bisRockFin == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 사용 UI 제거
			breakStoneUI->Destroy();

			// 슴베 연결 UI 생성
			connectSpearUI = GetWorld()->SpawnActor<ASJ_Actor_ConnectSpearUI>(bpConnectSpearUI, Param);

			cable = Cast<ACable>(UGameplayStatics::GetActorOfClass(GetWorld(), ACable::StaticClass()));
			// 아웃라인 켜주기
			cable->outLine->SetVisibility(true);

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			SetState(EFlowState::ConnectSpear);
		}
	}
}

// 슴베 연결하기
void ASJ_WoogaGameModeBase::ConnectSpear()
{
	if (cable->bIsConnect == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 사용 UI 제거
			connectSpearUI->Destroy();

			tieSpearUI = GetWorld()->SpawnActor<ASJ_Actor_TieSpearUI>(bpTieSpearUI, Param);

			string = Cast<AString>(UGameplayStatics::GetActorOfClass(GetWorld(), AString::StaticClass()));

			string->outLine->SetVisibility(true);

			nextDelayTime = 0;

			SetState(EFlowState::TieSpear);
		}
	}
}

// 슴베 묶기
void ASJ_WoogaGameModeBase::TieSpear()
{
	if (cable->bIsTie == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// 사용 UI 제거
			tieSpearUI->Destroy();

			makeHandAxRange->Destroy();

			// 홀로그램 생성
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpSpearHologram, Param);

			// 딜레이 변수 초기화
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
		// 범위 생성
		makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

		// 물고기 사냥 UI
		huntFishUI = GetWorld()->SpawnActor<ASJ_Actor_HuntFishUI>(bpHuntFishUI, Param);

		// 딜레이 변수 초기화
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
			// 사용 UI 제거
			// huntFishUI->Destroy();
			huntFishUI->SetActorHiddenInGame(true);

			catchFishUI = GetWorld()->SpawnActor<ASJ_Actor_CatchFishUI>(bpCatchFishUI, Param);
			// 잡을 물고기
			catchFish = Cast<ASJ_Actor_CatchFish>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_CatchFish::StaticClass()));
			catchFish->outlineFish->SetVisibility(true);

			// 딜레이변수 초기화
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
			// 사용 UI 제거
			catchFish->Destroy();

			goFryFishUI = GetWorld()->SpawnActor<ASJ_Actor_GoFryFishUI>(bpGoFryFishUI, Param);
			makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpGoToFry, Param);

			// 딜레이변수 초기화
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
			makeHandAxRange->Destroy();

			cookFishUI = GetWorld()->SpawnActor<ASJ_Actor_CookFishUI>(bpCookFishUI, Param);
			// 딜레이 변수 초기화
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
			// 사용 UI 제거
			cookFishUI->Destroy();

			// 익힌 물고기 먹기 UI
			eatFishUI = GetWorld()->SpawnActor<ASJ_Actor_EatFishUI>(bpEatFishUI, Param);

			// 딜레이 변수 초기화
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
			// 사용 UI 제거
			eatFishUI->Destroy();

			// 움집 가이드라인
			goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHutGuideLine, Param);

			// 움집 가이드라인 UI
			goToHutUI = GetWorld()->SpawnActor<ASJ_Actor_GoToHutUI>(bpGoToHutUI, Param);

			// 딜레이 변수 초기화
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
		// 사용 UI 제거
		goToHutUI->Destroy();

		// 제목 생성
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpHutTitle, Param);

		SetState(EFlowState::HutTitle);
	}
}
void ASJ_WoogaGameModeBase::HutTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// 움집만들기 UI 생성
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeHut, Param);

		// 가이드라인 제거
		goToGuideLine->Destroy();

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::HowToMakeHut);
	}
}
void ASJ_WoogaGameModeBase::HowToMakeHut()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 9.0f)
	{
		// UI 를 끄면
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// 움집만들기 UI 생성
				makeHutUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHutUI>(bpMakeHutUI, Param);

				lastHouse->SetActorHiddenInGame(false);

				TArray<AActor*> bpStick;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStick::StaticClass(), bpStick);

				if (bpStick.Num() > 0)
				{
					for (int i = 0; i < bpStick.Num(); i++)
					{
						AStick* emptyStick = nullptr;
						sticks.Add(emptyStick);
					}

					for (int i = 0; i < bpStick.Num(); i++)
					{
						auto sstick = Cast<AStick>(bpStick[i]);
						sticks[i] = sstick;
						sticks[i]->outLine->SetVisibility(true);
					}
				}

				// 딜레이변수 초기화
				bIsDelay = false;
				nextDelayTime = 0;
				howToNarTime = 0;

				SetState(EFlowState::MakeHut);
			}
		}
	}
}
void ASJ_WoogaGameModeBase::MakeHut()
{
	if (lastHouse->bisClear)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 10.0f)
		{
			makeHutUI->Destroy();

			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpHutHologram, Param);

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			SetState(EFlowState::CompleteHut);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteHut()
{
	// 플레이타임 18초 로직타임 22초
	UGameplayStatics::OpenLevel(this, TEXT("Outro"));
}

#pragma endregion

