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

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 맨 처음 불의 발견 교육으로 시작
	// SetState(EFlowState::InGame);

	// 테스트용 스테이트
	SetState(EFlowState::InGame);

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
	cuttingTwo = Cast<ACutting2>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting2::StaticClass()));
	cuttingTwo->SetActorHiddenInGame(true);

	// 자를 고기
	sliceMeat = Cast<ASliceMeat>(UGameplayStatics::GetActorOfClass(GetWorld(), ASliceMeat::StaticClass()));
	sliceMeat->SetActorHiddenInGame(true);

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
	case EFlowState::TestFunc:
		break;
	case EFlowState::GoToFireUse:
		GoToFireUse();
		break;
	case EFlowState::FireUseTitle:
		FireUseTitle();
		break;
	case EFlowState::FiringTwo:
		FiringTwo();
		break;
	case EFlowState::CookAndEat:
		CookAndEat();
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

		if (uiChange >= 2.0f)
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
		// 부싯돌 캐싱
		fireRockOne = Cast<AFireRock>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock::StaticClass()));
		fireRockTwo = Cast<AFireRock2>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock2::StaticClass()));

		// 부싯돌 아웃라인
		fireRockOne->outLine->SetVisibility(true);
		fireRockTwo->outLine->SetVisibility(true);

		// 불씨 UI 생성
		howToFire = GetWorld()->SpawnActor<ASJ_HowToFireUIActor>(howToFireUIActor, Param);

		// 사용된 UI 제거
		titleUI->Destroy();

		// 딜레이변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireUI);
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

		if (nextDelayTime >= 2.0f)
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

		if (nextDelayTime >= 2.0f)
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
		firePosition->outLine->SetHiddenInGame(true);
		fireStraw->outLine->SetHiddenInGame(true);

		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 2.0f)
		{
			// 홀로그램 생성
			hologramActor = GetWorld()->SpawnActor< ASJ_Actor_Hologram>(fireDisCoveryHologram, Param);

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			// 사용된 UI 제거
			breatheFireUI->Destroy();

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

	if (nextDelayTime >= 17.0f)
	{
		// 임무 완료 사운드
		//UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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
		// 가이드라인 생성
		goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpCollectGuideLine, Param);

		// 라이팅 낮 상태로 변경
		levelLight->isDay = true;

		watchInformUI->Destroy();

		// 딜레이 변수 초기화
		bIsDelay = false;
		nextDelayTime = 0;

		SetState(EFlowState::GoToCollectCourse);
	}
}

void ASJ_WoogaGameModeBase::GoToCollectState()
{
	if (goToGuideLine->isTrigger == true)
	{
		// 장작을 다시 사용해 주기 위한 세팅
		fireStraw->Destroy();

		// 채집하기 제목 UI 생성
		titleUI = GetWorld()->SpawnActor<class ASJ_Actor_TitleUI>(bpCollectTitleUI, Param);

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
		// 배고픔과 채집 안내 UI
		collectAndHungry = GetWorld()->SpawnActor<ASJ_Actor_CollectAndHungryUI>(bpCollectAndHungry, Param);

		// 제목 없애기
		titleUI->Destroy();

		// 가이드라인 없애기
		goToGuideLine->Destroy();

		// 딜레이변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::HowToCollectActorUI);
	}
}
void ASJ_WoogaGameModeBase::HowToCollectActorUI()
{
	// UI를 끄면 다음 상태로 넘어가기
	if (player->isClose == true)
	{
		bIsDelay = true;
	}
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 2.0f)
		{
			// 사과 캐싱하고 아웃라인 켜주기
			apple = Cast<AApple>(UGameplayStatics::GetActorOfClass(GetWorld(), AApple::StaticClass()));

			apple->outLine->SetVisibility(true);

			// 사과 채집과 먹기 UI
			eatAppleUI = GetWorld()->SpawnActor<ASJ_Actor_EatAppleUI>(bpEatAppleUI, Param);

			// 사용 UI 없애기
			collectAndHungry->Destroy();

			bIsDelay = false;
			nextDelayTime = 0;

			SetState(EFlowState::CollectAndEat);
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

		if (nextDelayTime >= 2.0f)
		{
			// 채집 홀로그램 생성
			hologramActor = GetWorld()->SpawnActor< ASJ_Actor_Hologram>(bpCollectHologram, Param);

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
		// 아웃라인 생성
		goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHandAxGuideLine, Param);

		nextDelayTime = 0;
		SetState(EFlowState::GoToFistAxCourse);
	}
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// 주먹도끼(사냥하기) 제목 생성
		titleUI = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpHandAxTitleUI, Param);

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
		// 제목 없애기
		titleUI->Destroy();

		// 가이드라인 없애기
		goToGuideLine->Destroy();

		// 딜레이변수 초기화
		nextDelayTime = 0;

		// 맘모스 생성
		mammothSpawn = GetWorld()->SpawnActor<ASJ_Actor_MammothSpawnDestroy>(bpMammothSpawn, Param);

		SetState(EFlowState::SeeMammoth);
	}
}
void ASJ_WoogaGameModeBase::SeeMammoth()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 15.0f)
	{
		// 맘모스 스폰 액터 제거
		mammothSpawn->Destroy();

		// 주먹도끼 돌 잡기 UI 생성
		handAxUI = GetWorld()->SpawnActor<ASJ_Actor_GrabHandAxUI>(bpHandAxUI, Param);

		// 주먹도끼 돌 아웃라인
		fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
		fistAxe->handHologramL->SetHiddenInGame(false);

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::GrabHandAx);
	}
}

void ASJ_WoogaGameModeBase::GrabHandAx()
{
	if (player->grabComp->bisGrabFistAxeR == true)
	{
		// UI 끄기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 2.0f)
		{
			// 멧돼지 생성
			boar = GetWorld()->SpawnActor<ASJ_Character_Boar>(bpRunboar, Param);

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
	if (boar->isHitBoar == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 2.0f)
		{
			// 사용된 UI 제거
			hitBoarUI->Destroy();

			// 주먹도끼 만들기 UI
			makeHandAxUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHandAxUI>(bpMakeHandAxUI, Param);

			// 주먹도끼 제작을 위한 장소 이동
			makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

			// 숨겨뒀던 죽은 돼지를 소환
			slicePig->SetActorHiddenInGame(false);

			nextDelayTime = 0;

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

		if (nextDelayTime >= 2.0f)
		{
			makeHandAxUI->Destroy();

			// 간접떼기 UI 생성
			indirectUI = GetWorld()->SpawnActor<ASJ_Actor_IndirectHitUI>(bpIndirectUI, Param);

			// 임무 완료 사운드
			//UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

			nextDelayTime = 0;

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

		if (nextDelayTime >= 2.0f)
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


		if (nextDelayTime >= 2.0f)
		{
			// 사용 UI 제거
			directUI->Destroy();

			// 딜레이변수 초기화
			nextDelayTime = 0;

			// 주먹도끼 홀로그램 생성
			hologramActor = GetWorld()->SpawnActor<ASJ_Actor_Hologram>(bpHandAxHologram, Param);

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

		// 돼지 정육 UI 생성
		cuttingPigUI = GetWorld()->SpawnActor<ASJ_Actor_CuttingPigUI>(bpCuttingPigUI, Param);

		cutting->SetActorHiddenInGame(false);
		cuttingTwo->SetActorHiddenInGame(false);
		sliceMeat->SetActorHiddenInGame(false);

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
	pigCutting = Cast<ACutting2>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting2::StaticClass()));

	if (pigCutting->bisfinish == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 2.0f)
		{
			// 가이드라인 생성
			goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpFIreUseGuideLine, Param);

			// 고기 들고가기 UI생성
			pickUpMeatUI = GetWorld()->SpawnActor<ASJ_Actor_PickUpMeatUI>(bpPickUpMeatUI, Param);

			// 도착 했을때 장작이 보이게 장작생성
			fireStraw = GetWorld()->SpawnActor<AFireStraw>(bpFireStraw, Param);

			// 장작에 숨만 불어 넣으면 불이 켜지도록 하게 하기 위한 변수 세팅
			fireStraw->bisReadyFire = true;
			fireStraw->bisOverlab = false;
			fireStraw->bisSmog = false;
			fireStraw->isClear = false;

			// 사용 UI 제거
			cuttingPigUI->Destroy();
			// 발판 제거
			makeHandAxRange->Destroy();

			// 딜레이 변수 초기화
			nextDelayTime = 0;

			SetState(EFlowState::GoToFireUse);
		}
	}
}
void ASJ_WoogaGameModeBase::TestFunc()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 3.0f)
	{
		// 가이드라인 생성
		goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpFIreUseGuideLine, Param);

		// 고기 들고가기 UI생성
		pickUpMeatUI = GetWorld()->SpawnActor<ASJ_Actor_PickUpMeatUI>(bpPickUpMeatUI, Param);

		// 도착 했을때 장작이 보이게 장작생성
		fireStraw = GetWorld()->SpawnActor<AFireStraw>(bpFireStraw, Param);

		// 장작에 숨만 불어 넣으면 불이 켜지도록 하게 하기 위한 변수 세팅
		fireStraw->bisReadyFire = true;
		fireStraw->bisOverlab = false;
		fireStraw->bisSmog = false;
		fireStraw->isClear = false;

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::GoToFireUse);
	}
}
void ASJ_WoogaGameModeBase::GoToFireUse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// 고기 들고가기 UI 제거
		pickUpMeatUI->Destroy();

		// 불의 활용 UI 생성
		titleUI = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpFireUseTitle, Param);

		SetState(EFlowState::FireUseTitle);
	}
}
void ASJ_WoogaGameModeBase::FireUseTitle()
{
	// 이때 이동을 막자
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// 제목 없애기
		titleUI->Destroy();

		// 가이드라인 없애기
		goToGuideLine->Destroy();

		// 숨을 불어 넣어주세요 UI 생성
		fireTwoUI = GetWorld()->SpawnActor<ASJ_Actor_FireTwoUI>(bpFireTwoUI, Param);

		// 딜레이변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::FiringTwo);
	}
}
void ASJ_WoogaGameModeBase::FiringTwo()
{
	if (fireStraw->isClear == true)
	{
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 3.0f)
		{
			// 딜레이 변수 초기화
			nextDelayTime = 0;

			// 사용 UI 파괴
			fireTwoUI->Destroy();

			SetState(EFlowState::CookAndEat);
		}
	}
}
void ASJ_WoogaGameModeBase::CookAndEat()
{
}
#pragma  endregion


