// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_Hologram.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_Hologram : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASJ_Actor_Hologram();

	UPROPERTY(EditAnywhere, Category = Hologram)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Hologram)
		class UStaticMeshComponent* plane;

	UPROPERTY(EditAnywhere, Category = Hologram)
		class UWidgetComponent* hologram;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		class ASJ_WoogaGameModeBase* gameModeBase;

	EHologramState holoState;
	void SetState(EHologramState state);
	EHologramState GetState();

	void TurnOnHologram();
	void PlayHologram();
	void TurnOffHologram();

	UPROPERTY()
		float createTime;

	UPROPERTY()
		float playTime;
	UPROPERTY(EditAnywhere, Category = Time)
		float playChangeTime;

	UPROPERTY()
		float destroyTime;

	// 지식 포인트
	UPROPERTY(EditAnywhere, Category = Point)
		TSubclassOf<class AFireEvent> knowledgePoint;

	// 플레이 사운드
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* propSound;
};
