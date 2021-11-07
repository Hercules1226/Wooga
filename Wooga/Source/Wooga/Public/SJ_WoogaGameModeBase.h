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
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* uiSound;

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
	class ASJ_Hologram* hologram;

	UPROPERTY(EditAnywhere, Category = Hologram)
		TSubclassOf<class ASJ_Hologram> fireDisCoveryHologram;

	// �÷��̾� ��ġ �ȳ� UI
	class ASJ_Actor_WatchInformUI* watchInformUI;

	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class ASJ_Actor_WatchInformUI> bpWatchInformUI;

	UPROPERTY(EditAnywhere, Category = GuideLine)
		AActor* gotoCollectGuideLine;

	class ASJ_GuidLine* guideLine;

	// ���� ��ҷ� �̵��ϱ� ���� ���̵� ����
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
		TSubclassOf<class ASJ_Hologram> bpCollectHologram;

	// ���(�ָԵ���)
	void HandAxTitle();
	void SeeMammoth();
	void GrabHandAx();
	void RunBoar();
	void HitBoar();

	// �ָԵ��� ���̵����
	class ASJ_Actor_GoToGuideLine* handAxGuideLine;
	UPROPERTY(EditAnywhere, Category =GuideLine)
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

	// ����� ����
	class ASJ_Actor_RunBoar* boar;
	UPROPERTY(EditAnywhere, Category = Boar)
	TSubclassOf<class ASJ_Actor_RunBoar> bpRunboar;

	// ����� óġ UI
	class ASJ_Actor_HitBoarUI* hitBoarUI;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_Actor_HitBoarUI> bpHitBoarUI;
};
