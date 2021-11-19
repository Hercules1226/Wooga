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
	// ��ü ���� �ӽ�
	EFlowState flowState;
	void SetState(EFlowState state);
	EFlowState GetState();

	// �÷��̾�
	class AVR_Player* player;

	// ���� �Ķ����
	FActorSpawnParameters Param;

	// ���� ���·� �Ѿ�� ������ Ÿ��
	UPROPERTY()
		float nextDelayTime;
	// ������Ÿ�� ī��Ʈ ����
	UPROPERTY()
		bool bIsDelay;

	// Ȱ�� UI ���� ����
	UPROPERTY()
		float uiChange;
	// UI�� �����Ϸ��� true
	UPROPERTY()
		bool bIsUIClose;
	// �ı� ���ð�
	UPROPERTY()
		bool isDelay;

	// �ָԵ��� ���� ���¿��� ���� ������ ���峻 �÷����� �������
	UPROPERTY()
	class ASlicePig* slicePig;
	UPROPERTY()
	class ACutting* cutting;
	UPROPERTY()
	class ACutting2* cuttingTwo;
	UPROPERTY()
	class ASliceMeat* sliceMeat;

	// ����Ʈ ����
	class ASJ_Actor_LevelLight* levelLight;

	// ���� ����
	void InGame();
	void ManipulateUI();
	void GrabActorUI();

	// ���۹�� UI 
	class ASJ_Actor_HowToManipulate* manipulateUI;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_HowToManipulate> bpManipulateUI;

	// �� UI ���� �����̸� ���� ��¹��UI ���� Ÿ�̸�
	FTimerHandle howToGrabUITimer;

	// ��� ��� �˷��ִ� UI
	class ASJ_HowToGrabUIActor* howToGrab;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_HowToGrabUIActor> howToGrabActor;

	// ���� ���� ��� �� Ÿ�̸�
	FTimerHandle titleTimer;

	// ���� �߰� ���� UI
	class ASJ_Actor_TitleUI* titleUI;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpFDTitle;

	// �ν˵�
	class AFireRock* fireRockOne;
	class AFireRock2* fireRockTwo;

	// ���� �߰� ����
	void FireDiscoveryTitle();
	void HowToFireUI();
	void HowToFireUINext();
	void Firing();
	void CompleteFireCourse();
	void InformWatch();
	void GoToCollectState();

	// UI Sound
	//UPROPERTY(EditAnywhere, Category = Sound)
	//class USoundBase* uiSound;

	// �����Ǵ� ��� �˷��ִ� UI
	class ASJ_HowToFireUIActor* howToFire;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_HowToFireUIActor> howToFireUIActor;

	// ��Ǫ���
	class AFirePosition* firePosition;
	// ȭ��
	class AFireStraw* fireStraw;

	// �����Ǵ� ��� ���� UI
	class ASJ_HowToFireNextUIActor* howToFireNext;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_HowToFireNextUIActor> howToFireNextUIActor;

	// �ҿ� ���� �Ҿ� �ִ� ��� UI
	class ASJ_Actor_BreatheFireUI* breatheFireUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_BreatheFireUI> bpBreatheFireUI;

	// ���� �߰� Ȧ�α׷�

	UPROPERTY()
	class ASJ_Hologram* hologram;

	UPROPERTY(EditAnywhere, Category = Hologram)
	TSubclassOf<class ASJ_Hologram> bpFDHologram;
	UPROPERTY()
		class ASJ_Actor_Hologram* hologramActor;

	UPROPERTY(EditAnywhere, Category = Hologram)
		TSubclassOf<class ASJ_Actor_Hologram> fireDisCoveryHologram;

	// �÷��̾� ��ġ �ȳ� UI
	class ASJ_Actor_WatchInformUI* watchInformUI;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_WatchInformUI> bpWatchInformUI;

	FVector p;

	UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;

	// ���̵����
	class ASJ_Actor_GoToGuideLine* goToGuideLine;
	UPROPERTY(EditAnywhere, Category = GuideLine)
		TSubclassOf<class ASJ_Actor_GoToGuideLine> bpCollectGuideLine;

	// ä���ϱ� ���� 
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpCollectTitleUI;

	// ä�� ����
	void CollectTitle();
	void HowToCollectActorUI();
	void CollectAndEat();
	void CompleteCollect();
	void GoToFistAxCourse();

	// ����İ� ä�� �ȳ� UI
	class ASJ_Actor_CollectAndHungryUI* collectAndHungry;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_CollectAndHungryUI> bpCollectAndHungry;

	// ���
	class AApple* apple;

	// ��� ä���� �Ա� UI
	class ASJ_Actor_EatAppleUI* eatAppleUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_EatAppleUI> bpEatAppleUI;

	// ä�� Ȧ�α׷�
	UPROPERTY(EditAnywhere, Category = Hologram)
		TSubclassOf<class ASJ_Actor_Hologram> bpCollectHologram;

	// ���(�ָԵ���)
	void HandAxTitle();
	void SeeMammoth();
	void GrabHandAx();
	void RunBoar();
	void HitBoar();
	void MakeHandAx();
	void IndirectHit();
	void DirectHit();
	void CompleteHandAx();

	// �ָԵ��� ���̵����
	UPROPERTY(EditAnywhere, Category = GuideLine)
		TSubclassOf<class ASJ_Actor_GoToGuideLine> bpHandAxGuideLine;

	// �ָԵ��� ����(����ϱ�)
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpHandAxTitleUI;

	// ���� ���� 
	class ASJ_Actor_MammothSpawnDestroy* mammothSpawn;
	UPROPERTY(EditAnywhere, Category = Mammoth)
		TSubclassOf<class ASJ_Actor_MammothSpawnDestroy> bpMammothSpawn;

	// ���� ī�޶� ����ũ
	UPROPERTY(EditAnywhere, Category = Mammoth)
		TSubclassOf<class UCameraShakeBase> mammothCameraShake;

	// ī�޶� ����ũ �÷��� �ð�
	UPROPERTY()
		float mammothShakeTime;

	// �ָԵ��� �� ��� UI
	class ASJ_Actor_GrabHandAxUI* handAxUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_GrabHandAxUI> bpHandAxUI;

	class AFistAxe* fistAxe;

	// ����� ����
	class ASJ_Character_Boar* boar;
	UPROPERTY(EditAnywhere, Category = Boar)
		TSubclassOf<class ASJ_Character_Boar> bpRunboar;

	// ����� óġ UI
	class ASJ_Actor_HitBoarUI* hitBoarUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_HitBoarUI> bpHitBoarUI;

	// �ָԵ��� ����� UI
	class ASJ_Actor_MakeHandAxUI* makeHandAxUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_MakeHandAxUI> bpMakeHandAxUI;

	// �ָԵ����� ����� ���� ���̵����
	UPROPERTY()
	class ASJ_Actor_MakeRange* makeHandAxRange;
	UPROPERTY(EditAnywhere, Category = Range)
	TSubclassOf<class ASJ_Actor_MakeRange> bpMakeHandAxRange;

	// �������� UI
	class ASJ_Actor_IndirectHitUI* indirectUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_IndirectHitUI> bpIndirectUI;

	// �������� UI
	class ASJ_Actor_DirectHitUI* directUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_DirectHitUI> bpDirectHitUI;

	// �ָԵ��� Ȧ�α׷�
	UPROPERTY(EditAnywhere, Category = Hologram)
		TSubclassOf<class ASJ_Actor_Hologram> bpHandAxHologram;

	// ���� Ȱ��
	void CuttingPig();
	void TestFunc();
	void GoToFireUse();
	void FireUseTitle();
	void FiringTwo();
	void CookAndEat();

	// ���� �� ����
	UPROPERTY(EditAnywhere, Category = FireStraw)
		TSubclassOf<class AFireStraw> bpFireStraw;

	// ���� ���� UI
	UPROPERTY()
		class ASJ_Actor_CuttingPigUI* cuttingPigUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_CuttingPigUI> bpCuttingPigUI;

	// ��� ����� UI
	UPROPERTY()
		class ASJ_Actor_PickUpMeatUI* pickUpMeatUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_PickUpMeatUI> bpPickUpMeatUI;

	// ���� ���� ���
	UPROPERTY()
		class ACutting2* pigCutting;

	// ���� Ȱ�� ���̵����
	UPROPERTY(EditAnywhere, Category = GuideLine)
		TSubclassOf<class ASJ_Actor_GoToGuideLine> bpFIreUseGuideLine;

	// ���� Ȱ�� ����
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_TitleUI> bpFireUseTitle;

	// ���� �Ҿ� �־��ּ��� UI
	UPROPERTY()
		class ASJ_Actor_FireTwoUI* fireTwoUI;
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_FireTwoUI> bpFireTwoUI;
};
