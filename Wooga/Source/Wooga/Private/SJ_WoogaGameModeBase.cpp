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
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "SJ_Actor_GoToGuideLine.h"
#include "SJ_Actor_MammothSpawnDestroy.h"
#include "SJ_Actor_RunBoar.h"
#include "SJ_Actor_GrabHandAxUI.h"
#include "SJ_Actor_HitBoarUI.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 맨 처음 불의 발견 교육으로 시작
	SetState(EFlowState::CompleteCollect);

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
	}

	// UI 로직
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
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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

			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			howToFireNext = GetWorld()->SpawnActor<ASJ_HowToFireNextUIActor>(howToFireNextUIActor, Param);

			// 사용된 UI 제거
			howToFire->Destroy();

			// 임무 완료 사운드
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
		// UI 꺼주기
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 2.0f)
		{
			// 임무 완료 사운드
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 3.0f)
		{
			// UI 꺼주기
			bIsUIClose = true;

			// 홀로그램 생성
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(fireDisCoveryHologram, Param);

			// UI Sound
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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

	if (nextDelayTime >= 20.0f)
	{
		// 임무 완료 사운드
		UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		// 지식 안내 UI 생성
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		watchInformUI = GetWorld()->SpawnActor<ASJ_Actor_WatchInformUI>(bpWatchInformUI, Param);

		// 사용된 홀로그램 제거
		hologram->Destroy();

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
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		informUI = GetWorld()->SpawnActor<ASJ_InformUIPannel>(bpGoToCollect, Param);

		watchInformUI->Destroy();

		// 딜레이 변수 초기화
		bIsDelay = false;
		nextDelayTime = 0;

		SetState(EFlowState::GoToCollectCourse);
	}
}

void ASJ_WoogaGameModeBase::GoToCollectState()
{
	// InformUIPannel 에서 관리
	informUI = Cast<ASJ_InformUIPannel>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_InformUIPannel::StaticClass()));

	if (informUI->isTrigger == true)
	{
		// 채집하기 제목 UI 생성
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		collectAndHungry = GetWorld()->SpawnActor<ASJ_Actor_CollectAndHungryUI>(bpCollectAndHungry, Param);

		// 제목 없애기
		titleUI->Destroy();

		// 임무 완료 사운드
		UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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

		if (nextDelayTime >= 3.0f)
		{
			// 사과 캐싱하고 아웃라인 켜주기
			apple = Cast<AApple>(UGameplayStatics::GetActorOfClass(GetWorld(), AApple::StaticClass()));

			apple->outLine->SetVisibility(true);

			// 임무 완료 사운드
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

			// 사과 채집과 먹기 UI
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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

		if (nextDelayTime >= 3.0f)
		{
			// 채집 홀로그램 생성
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpCollectHologram, Param);

			// 임무 완료 사운드
			UGameplayStatics::PlaySound2D(GetWorld(), uiSound);

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

	if (nextDelayTime >= 3.0f)
	{
		// 아웃라인 생성
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		handAxGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHandAxGuideLine, Param);

		nextDelayTime = 0;
		SetState(EFlowState::GoToFistAxCourse);
	}
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
	if (handAxGuideLine->isTrigger == true)
	{
		// 주먹도끼(사냥하기) 제목 생성
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		titleUI = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpHandAxTitleUI, Param);

		UE_LOG(LogTemp, Warning, TEXT("RangeIn"));

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

		// 딜레이변수 초기화
		nextDelayTime = 0;

		// 맘모스 생성
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		mammothSpawn = GetWorld()->SpawnActor<ASJ_Actor_MammothSpawnDestroy>(bpMammothSpawn, Param);

		UE_LOG(LogTemp, Warning, TEXT("Spawn Mammoth"));

		SetState(EFlowState::SeeMammoth);
	}
}
void ASJ_WoogaGameModeBase::SeeMammoth()
{
	// 카메라 쉐이크와 사운드 플레이
	mammothShakeTime += GetWorld()->DeltaTimeSeconds;

	// 1초마다 한번씩 카메라 쉐이크 플레이
	if (mammothShakeTime >= 1.0f)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(mammothCameraShake);

		mammothShakeTime = 0;
	}

	nextDelayTime += GetWorld()->DeltaTimeSeconds;
	
	if (nextDelayTime >= 15.0f)
	{
		// 맘모스 스폰 액터 제거
		mammothSpawn->Destroy();

		// 주먹도끼 돌 잡기 UI 생성
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		handAxUI = GetWorld()->SpawnActor<ASJ_Actor_GrabHandAxUI>(bpHandAxUI, Param);
		
		// 주먹도끼 돌 아웃라인

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::GrabHandAx);
	}
}

void ASJ_WoogaGameModeBase::GrabHandAx()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 10.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("GrabHandAx"));
		// UI 끄기
		bIsUIClose = true;

		// 멧돼지 생성
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		boar = GetWorld()->SpawnActor<ASJ_Actor_RunBoar>(bpRunboar, Param);

		// 딜레이 변수 초기화
		nextDelayTime = 0;

		SetState(EFlowState::RunBoar);
	}
	if (player->grabComp->bisfistAxeR == true)
	{
		
	}
}
void ASJ_WoogaGameModeBase::RunBoar()
{
	if (boar->boarState == EBoarState::SlowMotion)
	{
		// 멧돼지 가격 UI
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		hitBoarUI = GetWorld()->SpawnActor<ASJ_Actor_HitBoarUI>(bpHitBoarUI, Param);

		SetState(EFlowState::HitBoar);
	}
}

void ASJ_WoogaGameModeBase::HitBoar()
{

}
#pragma endregion


