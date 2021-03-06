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

	// 생성 파라미터
	FActorSpawnParameters Param;

	// 다음 상태로 넘어가는 딜레이 타임
	UPROPERTY()
		float nextDelayTime;
	// 딜레이타임 카운트 여부
	UPROPERTY()
		bool bIsDelay;

	UPROPERTY()
	float handAxDelayTime;
	UPROPERTY()
	bool isHandAxDelay;

	// 활동 UI 관련 변수
	UPROPERTY()
		float uiChange;
	// UI를 종료하려면 true
	UPROPERTY()
		bool bIsUIClose;
	// 파괴 대기시간
	UPROPERTY()
		bool isDelay;

	// 주먹도끼 제작 상태에서 죽은 돼지는 월드내 올려놓고 사용하자
	UPROPERTY()
	class ASlicePig* slicePig;
	UPROPERTY()
	class ACutting* cutting;
	UPROPERTY()
	class ACutting2* cuttingTwo;
	UPROPERTY()
	class ASliceMeat* sliceMeat;
	UPROPERTY()
	class ATomahowk* tomahowk;

	UPROPERTY()
	class AMoveSpline* moveSpine;

	// 라이트 설정
	class ASJ_Actor_LevelLight* levelLight;

	// 새
	UPROPERTY()
	TArray<class ASJ_Actor_Bird*> birds;

	// 사슴
	UPROPERTY()
	TArray<class ASJ_Actor_RunDeer*> deers;

	// 게임 시작
	void InGame();
	void ManipulateUI();
	void GrabActorUI();

	// 조작방법 UI
	UPROPERTY()
	class ASJ_Actor_SystemUI* systemUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_SystemUI> bpMoveSystemUI;

	// 잡는방법 UI
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_SystemUI> bpGrabSystemUI;

	UPROPERTY()
	float systemUIDelayTime;

	// 불의 발견 제목 UI
	class ASJ_Actor_TitleUI* titleUI;

	class ASJ_Actor_Title* title;
	UPROPERTY(EditAnywhere, Category = Title)
	TSubclassOf<class ASJ_Actor_Title> bpFDTitle;

	// 부싯돌
	class AFireRock* fireRockOne;
	class AFireRock2* fireRockTwo;

	// 불의 발견 교육
	void FireDiscoveryTitle();
	void HowToFIreDiscovery();
	void HowToFireUI();
	void HowToFireUINext();
	void Firing();
	void CompleteFireCourse();
	void InformWatch();
	void SpawnCollectGuideLine();
	void GoToCollectState();

	// UI Sound
	//UPROPERTY(EditAnywhere, Category = Sound)
	//class USoundBase* uiSound;

	// 불피우기 전체 안내 UI
	UPROPERTY()
	class ASJ_Actor_HowToFlow* howToFlow;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HowToFlow> bpFDHowToFlow;

	// 불지피는 방법 알려주는 UI
	UPROPERTY()
	class ASJ_HowToFireUIActor* howToFire;

	// 설명 나래이션 재생시간
	UPROPERTY()
	float howToNarTime;

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
	UPROPERTY()
	class ASJ_Hologram* hologram;

	UPROPERTY(EditAnywhere, Category = Hologram)
	TSubclassOf<class ASJ_Hologram> bpFDHologram;

	// 플레이어 워치 안내 UI
	UPROPERTY(EditAnywhere,Category = UI)
	TSubclassOf<class ASJ_Actor_SystemUI> bpKnowledgeInformUI;

	FVector p;

	UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;

	// 가이드라인
	class ASJ_Actor_GoToGuideLine* goToGuideLine;
	UPROPERTY(EditAnywhere, Category = GuideLine)
		TSubclassOf<class ASJ_Actor_GoToGuideLine> bpCollectGuideLine;

	// 채집하기 제목 
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpCollectTitleUI;

	UPROPERTY(EditAnywhere, Category = Title)
		TSubclassOf<class ASJ_Actor_Title> bpCollectTitle;

	// 채집 교육
	void CollectTitle();
	void HowToCollect();
	void CollectAndEat();
	void CompleteCollect();
	void SpawnHandAxGuideLine();
	void GoToFistAxCourse();

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HowToFlow> bpCollectHowToFlow;

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
	void HowToHunt();
	void GrabHandAx();
	void RunBoar();
	void HitBoar();
	void MakeHandAx();
	void HowToMakeHandAx();
	void IndirectHit();
	void DirectHit();
	void CompleteHandAx();

	// 주먹도끼 가이드라인
	UPROPERTY(EditAnywhere, Category = GuideLine)
		TSubclassOf<class ASJ_Actor_GoToGuideLine> bpHandAxGuideLine;

	// 주먹도끼 제목(사냥하기)
	UPROPERTY(EditAnywhere, Category = Title)
		TSubclassOf<class ASJ_Actor_Title> bpHandAxTitle;

	// 새 소리
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* birdSound;

	// 사냥 하는법
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HowToFlow> bpHowToHunt;

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

	// 맘모스 발소리만 들리는 플레이시간
	UPROPERTY()
	float mammothFootStepPlayTime;

	UPROPERTY(EditAnywhere, Category = Sound)
	USoundBase* footStepSound;

	UPROPERTY()
	class ASJ_Actor_Mammoth* mammoth;

	// 주먹도끼 돌 잡기 UI
	class ASJ_Actor_GrabHandAxUI* handAxUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_GrabHandAxUI> bpHandAxUI;

	class AFistAxe* fistAxe;

	// 멧돼지 생성
	class ASJ_Character_Boar* boar;
	UPROPERTY(EditAnywhere, Category = Boar)
		TSubclassOf<class ASJ_Character_Boar> bpRunboar;

	// 멧돼지 처치 UI
	class ASJ_Actor_HitBoarUI* hitBoarUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_HitBoarUI> bpHitBoarUI;

	// 주먹도끼 만들기 UI
	class ASJ_Actor_MakeHandAxUI* makeHandAxUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_MakeHandAxUI> bpMakeHandAxUI;

	// 주먹도끼를 만들기 위한 가이드라인
	UPROPERTY()
	class ASJ_Actor_MakeRange* makeHandAxRange;
	UPROPERTY(EditAnywhere, Category = Range)
	TSubclassOf<class ASJ_Actor_MakeRange> bpMakeHandAxRange;

	// 주먹도끼 만드는 방법
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HowToFlow> bpHowToMakeHandAx;

	UPROPERTY()
	class AActor* hitPoint;
	// 히트 포인트
	UPROPERTY(EditAnywhere, Category = HitPoint)
	TSubclassOf<AActor> bpHitPoint;

	// 간접떼기 UI
	class ASJ_Actor_IndirectHitUI* indirectUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_IndirectHitUI> bpIndirectUI;

	// 직접떼기 UI
	class ASJ_Actor_DirectHitUI* directUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_DirectHitUI> bpDirectHitUI;

	// 주먹도끼 홀로그램
	UPROPERTY(EditAnywhere, Category = Hologram)
	TSubclassOf<class ASJ_Hologram> bpHandAxHologram;

	// 불의 활용
	void CuttingPig();
	void GoToFireUse();
	void FireUseTitle();
	void HowToFireUse();
	void FiringTwo();
	void CookMeat();
	void EatMeat();
	void CompleteFireUse();
	void GoToSpear();

	// 생성 할 장작
	UPROPERTY(EditAnywhere, Category = FireStraw)
		TSubclassOf<class AFireStraw> bpFireStraw;

	// 돼지 정육 UI
	UPROPERTY()
		class ASJ_Actor_CuttingPigUI* cuttingPigUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_CuttingPigUI> bpCuttingPigUI;

	// 고기 들고가기 UI
	UPROPERTY()
		class ASJ_Actor_PickUpMeatUI* pickUpMeatUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_PickUpMeatUI> bpPickUpMeatUI;

	// 돼지 정육 기능
	UPROPERTY()
		class ACutting* pigCutting;

	// 불의 활용 가이드라인
	UPROPERTY(EditAnywhere, Category = GuideLine)
		TSubclassOf<class ASJ_Actor_GoToGuideLine> bpFIreUseGuideLine;

	// 불의 활용 제목
	UPROPERTY(EditAnywhere, Category = Title)
		TSubclassOf<class ASJ_Actor_Title> bpFireUseTitle;

		UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_HowToFlow> bpHowToFireUse;

	// 숨을 불어 넣어주세요 UI
	UPROPERTY()
		class ASJ_Actor_FireTwoUI* fireTwoUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_FireTwoUI> bpFireTwoUI;

	// 요리 UI
	UPROPERTY()
	class ASJ_Actor_CookUI* cookUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_CookUI> bpCookUI;

	// 먹기 UI
	UPROPERTY()
	class ASJ_Actor_EatMeatUI* eatMeatUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_EatMeatUI> bpEatMeatUI;

	// 불의 활용 홀로그램 
	UPROPERTY(EditAnywhere, Category = Hologram)
	TSubclassOf<class ASJ_Hologram> bpFireUseHologram;

	// 슴베찌르개까지 가이드라인
	UPROPERTY(EditAnywhere, Category = GuideLine)
	TSubclassOf<class ASJ_Actor_GoToGuideLine> bpSpearGuideLine;

	// 뼈를 들고 이동하시오 UI
	UPROPERTY()
	class ASJ_Actor_GrabTomahowkUI* grabTomahowk;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_GrabTomahowkUI> bpGrabTomahowkUI;

	// 슴베찌르개
	void SpearTitle();
	void MakeSpear();
	void HowToMakeSpear();
	void TakeRock();
	void ConnectSpear();
	void TieSpear();
	void CompleteSpear();
	void HuntFish();
	void CatchFish();
	void GoBackFireStraw();
	void CanFreeMove();
	void GoToCookFish();
	void CookFish();
	void EatFish();

	// 슴베찌르개 제목
	UPROPERTY(EditAnywhere, Category = Title)
	TSubclassOf<class ASJ_Actor_Title> bpSpearTitle;

	// 슴베찌르개 만드는 방법 UI
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HowToFlow> bpHowToMakeSpear;

	// 슴베찌르개 제작 UI
	UPROPERTY()
	class ASJ_Actor_MakeSpearUI* makeSpearUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_MakeSpearUI> bpMakeSpearUI;

	// 뼈를 이용해 돌을 다듬으세요
	UPROPERTY()
	class ASJ_Actor_BreakStoneUI* breakStoneUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_BreakStoneUI> bpBreakStoneUI;

	// 슴베
	UPROPERTY()
	class ASumjjiRock* sumjjiRock;

	// 나뭇가지를 주워 슴베와 연결
	UPROPERTY()
	class ASJ_Actor_ConnectSpearUI* connectSpearUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_ConnectSpearUI> bpConnectSpearUI;

	// 슴베 막대기
	UPROPERTY()
	class ACable* cable;

	// 나무가지 묶기 UI
	UPROPERTY()
	class ASJ_Actor_TieSpearUI* tieSpearUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_TieSpearUI> bpTieSpearUI;

	// 덩쿨
	UPROPERTY()
	class AString* string;

	//  슴베찌르개 홀로그램
	UPROPERTY(EditAnywhere, Category = Hologram)
	TSubclassOf<class ASJ_Hologram> bpSpearHologram;

	// 물고기 사냥 UI
	UPROPERTY()
	class ASJ_Actor_HuntFishUI* huntFishUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HuntFishUI> bpHuntFishUI;

	// 물고기 잡기 UI 
	UPROPERTY()
	class ASJ_Actor_CatchFishUI* catchFishUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_CatchFishUI> bpCatchFishUI;

	// 잡을 물고기
	UPROPERTY()
	class ASJ_Actor_CatchFish* catchFish;

	// 물고기 요리 UI
	UPROPERTY()
	class ASJ_Actor_GoFryFishUI* goFryFishUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_GoFryFishUI> bpGoFryFishUI;

	// 플레이어 자유이동 범위
	UPROPERTY()
	class ASJ_ChangeFreeMove* freeMove;

	// 화롯대 유도 가이드라인
	UPROPERTY(EditAnywhere, Category = Range)
	TSubclassOf<class ASJ_Actor_MakeRange> bpGoToFry;

	// 자유이동 안내
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_SystemUI> bpFreeMoveUI;

	// 물고기 익히기 UI
	UPROPERTY()
	class ASJ_Actor_CookFishUI* cookFishUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_CookFishUI> bpCookFishUI;

	// 물고기 먹기 UI
	UPROPERTY()
	class ASJ_Actor_EatFishUI* eatFishUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_EatFishUI> bpEatFishUI;

	void SpawnHutGuideLine();
	// 움집제작
	void GoToHut();
	void HutTitle();
	void HowToMakeHut();
	void MakeHut();
	void CompleteHut();
	void OutGame();

	// 움집 제작 가이드라인
	UPROPERTY(EditAnywhere, Category = GuiedLine)
	TSubclassOf<class ASJ_Actor_GoToGuideLine> bpHutGuideLine;

	// 움집 가이드라인 UI
	UPROPERTY()
	class ASJ_Actor_GoToHutUI* goToHutUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_GoToHutUI> bpGoToHutUI;

	// 움집 제목
	UPROPERTY(EditAnywhere, Category = Title)
	TSubclassOf<class ASJ_Actor_Title> bpHutTitle;

	// 움집 제작 방법
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HowToFlow> bpHowToMakeHut;

	// 나뭇가지
	TArray<class AStick*> sticks;

	// 움집 제작 UI
	UPROPERTY()
	class ASJ_Actor_MakeHutUI* makeHutUI;
	UPROPERTY(EditAnywhere, Category = UI )
	TSubclassOf<class ASJ_Actor_MakeHutUI> bpMakeHutUI;

	// 움집
	UPROPERTY()
	class ALastHouse* lastHouse;

	// 움집 홀로그램
	UPROPERTY(EditAnywhere, Category = Hologram)
	TSubclassOf<class ASJ_Hologram> bpHutHologram;
};
