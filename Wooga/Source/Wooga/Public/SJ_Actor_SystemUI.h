// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_SystemUI.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_SystemUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_SystemUI();

	UPROPERTY(EditAnywhere, Category = UI)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = UI)
	class UStaticMeshComponent* plane;

	UPROPERTY(EditAnywhere, Category = UI)
	class UWidgetComponent* widgetComp;

	UPROPERTY(EditAnywhere, Category = UI)
	class UStaticMeshComponent* nextController;

	UPROPERTY(EditAnywhere, Category = UI)
	class UStaticMeshComponent* nextBlink;

	UPROPERTY(EditAnywhere, Category = UI)
		class UWidgetComponent* nextWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ASJ_WoogaGameModeBase* gameModeBase;

	class AVR_Player* player;

	class USJ_UI_Next* nextUI; 

	class USJ_UI_SystemUI* systemUI;

	EUIState uiState;
	EUIState GetState();
	void SetState(EUIState state);

	void On();
	void Stay();
	void Next();
	void Off();

	UPROPERTY()
	float currentTime;

	UPROPERTY()
	float blinkTime;

	UPROPERTY()
		float startDissolveParam;
	UPROPERTY()
		float endDissolveParam;

	// 켜지고 꺼지는 시간
	UPROPERTY()
		float onTime;
	UPROPERTY()
		float offTime;
};
