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

	// ��Ƽ���� ������ ����
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
	void OffSature();
};
