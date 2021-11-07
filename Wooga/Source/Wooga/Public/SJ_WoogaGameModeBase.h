// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/GameModeBase.h"
#include "SJ_WoogaGameModeBase.generated.h"

UCLASS()
class WOOGA_API ASJ_WoogaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASJ_WoogaGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	// 전체 상태 머신
	EFlowState flowState;
	void SetState(EFlowState state);
	EFlowState GetState();

	// 플레이어
	class AVR_Player* player;

	// 다음 상태로 넘어가는 딜레이 타임
	UPROPERTY()
	float nextDelayTime;
	// 딜레이타임 카운트 여부
	UPROPERTY()
	bool bIsDelay;

	// 활동 UI 관련 변수
	UPROPERTY()
	float uiChange;
	// UI를 종료하려면 true
	UPROPERTY()
	bool bIsUIClose;

	// 게임 시작
	void InGame();
	void ManipulateUI();
	void GrabActorUI();

	// 조작방법 UI 
	class ASJ_Actor_HowToManipulate* manipulateUI;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_HowToManipulate> bpManipulateUI;

	// 두 UI 간에 딜레이를 위한 잡는방법UI 생성 타이머
	FTimerHandle howToGrabUITimer;

	// 잡는 방법 알려주는 UI
	class ASJ_HowToGrabUIActor* howToGrab;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_HowToGrabUIActor> howToGrabActor;

	// 제목 생성 기능 및 타이머
	FTimerHandle titleTimer;

	// 불의 발견 제목 UI
	class ASJ_Actor_TitleUI* titleUI;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpFDTitle;

	// 부싯돌
	class AFireRock* fireRockOne;
	class AFireRock2* fireRockTwo;

	// 불의 발견 교육
	void FireDiscoveryTitle();
	void HowToFireUI();
	void HowToFireUINext();
	void Firing();
	void CompleteFireCourse();
	void InformWatch();
	void GoToCollectState();

	// UI Sound
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* uiSound;

	// 불지피는 방법 알려주는 UI
	class ASJ_HowToFireUIActor* howToFire;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_HowToFireUIActor> howToFireUIActor;

	// 지푸라기
	class AFirePosition* firePosition;
	// 화로
	class AFireStraw* fireStraw;

	// 불지피는 방법 다음 UI
	class ASJ_HowToFireNextUIActor* howToFireNext;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_HowToFireNextUIActor> howToFireNextUIActor;

	// 불에 숨을 불어 넣는 방법 UI
	class ASJ_Actor_BreatheFireUI* breatheFireUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_BreatheFireUI> bpBreatheFireUI;

	// 불의 발견 홀로그램
	class ASJ_Hologram* hologram;

	UPROPERTY(EditAnywhere, Category = Hologram)
		TSubclassOf<class ASJ_Hologram> fireDisCoveryHologram;

	// 플레이어 워치 안내 UI
	class ASJ_Actor_WatchInformUI* watchInformUI;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_WatchInformUI> bpWatchInformUI;

	UPROPERTY(EditAnywhere, Category = GuideLine)
		AActor* gotoCollectGuideLine;

	class ASJ_GuidLine* guideLine;

	// 다음 장소로 이동하기 위한 가이드 라인
	UPROPERTY(EditAnywhere, Category = GuideLine)
		TSubclassOf<class ASJ_GuidLine> bbgoToCollectGuideLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
		class ADirectionalLight* dirLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
		class ADirectionalLight* sunLight;

	FVector p;

	UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;

	// Inform UI Pannel
	class ASJ_InformUIPannel* informUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf <class ASJ_InformUIPannel> bpGoToCollect;

	// 채집하기 제목 
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpCollectTitleUI;

	// 채집 교육
	void CollectTitle();
	void HowToCollectActorUI();
	void CollectAndEat();
	void CompleteCollect();
	void GoToFistAxCourse();

	// 배고픔과 채집 안내 UI
	class ASJ_Actor_CollectAndHungryUI* collectAndHungry;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_CollectAndHungryUI> bpCollectAndHungry;

	// 사과
	class AApple* apple;

	// 사과 채집과 먹기 UI
	class ASJ_Actor_EatAppleUI* eatAppleUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_EatAppleUI> bpEatAppleUI;

	// 채집 홀로그램
	UPROPERTY(EditAnywhere, Category = Hologram)
		TSubclassOf<class ASJ_Hologram> bpCollectHologram;

	// 사냥(주먹도끼)
	void HandAxTitle();
	void SeeMammoth();
	void GrabHandAx();
	void RunBoar();
	void HitBoar();

	// 주먹도끼 가이드라인
	class ASJ_Actor_GoToGuideLine* handAxGuideLine;
	UPROPERTY(EditAnywhere, Category =GuideLine)
	TSubclassOf<class ASJ_Actor_GoToGuideLine> bpHandAxGuideLine;

	// 주먹도끼 제목(사냥하기)
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpHandAxTitleUI;

	// 맘모스 생성 
	class ASJ_Actor_MammothSpawnDestroy* mammothSpawn;
	UPROPERTY(EditAnywhere, Category = Mammoth)
	TSubclassOf<class ASJ_Actor_MammothSpawnDestroy> bpMammothSpawn;

	// 맘모스 카메라 쉐이크
	UPROPERTY(EditAnywhere, Category = Mammoth)
	TSubclassOf<class UCameraShakeBase> mammothCameraShake;

	// 카메라 쉐이크 플레이 시간
	UPROPERTY()
	float mammothShakeTime;

	// 주먹도끼 돌 잡기 UI
	class ASJ_Actor_GrabHandAxUI* handAxUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_GrabHandAxUI> bpHandAxUI;

	// 멧돼지 생성
	class ASJ_Actor_RunBoar* boar;
	UPROPERTY(EditAnywhere, Category = Boar)
	TSubclassOf<class ASJ_Actor_RunBoar> bpRunboar;

	// 멧돼지 처치 UI
	class ASJ_Actor_HitBoarUI* hitBoarUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HitBoarUI> bpHitBoarUI;
};
