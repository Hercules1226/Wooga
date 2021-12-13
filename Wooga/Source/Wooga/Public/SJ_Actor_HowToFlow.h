// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_HowToFlow.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_HowToFlow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_HowToFlow();
	
	UPROPERTY(EditAnywhere, Category = HowToFlow)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = HowToFlow)
	class UStaticMeshComponent* howToPlane;

	UPROPERTY(EditAnywhere, Category = HowToFlow)
	class UPostProcessComponent* howToPost;

	UPROPERTY(EditAnywhere, Category = HowToFlow)
	class UWidgetComponent* howToUI;

	UPROPERTY(EditAnywhere, Category = HowToFlow, BlueprintReadWrite)
	class UWidgetComponent* nextWidget;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ASJ_WoogaGameModeBase* gameMode;

	UPROPERTY()
	class AVR_Player* player;

	UPROPERTY()
	class USJ_UI_Next* nextUI;

	UPROPERTY()
	class USJ_UI_Flow* flowUI;

	UPROPERTY()
	int32 flowIndex = 1;

	UPROPERTY()
	TArray<class AArrow1*> arrow1s;

	UPROPERTY()
		class AArrow2* arrow2;

	UPROPERTY()
		class AArrow3* arrow3;

	UPROPERTY()
		class AArrow4* arrow4;

	UPROPERTY()
		class AArrow5* arrow5;

	UPROPERTY()
	TArray<class AArrow6*> arrow6s;

	UPROPERTY()
	TArray<class AArrow7*> arrow7s;

	// ��Ƽ���� ������ ����
	UPROPERTY()
	float beginDissolveParam;
	UPROPERTY()
	float startDissolveParam;
	UPROPERTY()
	float endDissolveParam;

	// ����Ʈ���μ��� ����
	UPROPERTY(EditAnywhere, Category = Setting)
	struct FPostProcessSettings startParam;

	UPROPERTY(EditAnywhere, Category = Setting)
		struct FPostProcessSettings onParam;

	UPROPERTY(EditAnywhere, Category = Setting)
		struct FPostProcessSettings offParam;

	// ������ ������ �ð�
	UPROPERTY()
	float onTime;
	UPROPERTY()
	float offTime;

	// ĸ��ȭ
	ESaturateState saturateState;
	ESaturateState GetState();
	void SetState(ESaturateState state);

	void OnSature();
	void Stay();
	void Next();
	void OffSature();

	// ���� �����̼�
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* howToSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* onSound;

	// �����̼� ���� �ð�
	UPROPERTY()
	float playTime;

	UPROPERTY()
	float currentTime;

	UPROPERTY()
	bool isDelay = false;
};
