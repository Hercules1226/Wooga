// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "Watch6.generated.h"

UCLASS()
class WOOGA_API AWatch6 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWatch6();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setting)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* watch;

	UPROPERTY()
		class AVR_Player* player;

	EBlinkState blinkState;
	EBlinkState GetState();
	void SetState(EBlinkState state);

	void Idle();
	void Blink();
	void UnBlink();

	UPROPERTY()
		float speed = 10.f;

	UPROPERTY()
		float currentTime;

	UPROPERTY()
		bool bisEnd = false;

	UPROPERTY()
		bool bisStartFollow = true;

	UPROPERTY()
		bool isBlink;

	UPROPERTY()
		float playTime;

	UPROPERTY()
		class AIconSpot* spot;

	UPROPERTY()
		class ASJ_Actor_KnowledgePoint* pointMachine;

	UPROPERTY(EditAnywhere, Category = "Fire")
		class UParticleSystem* effectFactory;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon6* icon6;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon6> icon6Factory;

	UPROPERTY()
		float endingCurrentTime;

	UPROPERTY()
		bool bisfinish = false;

	// È¸Àü
	UPROPERTY()
		FVector dir;

	UPROPERTY()
		FRotator targetrot;

	UPROPERTY()
		FRotator curRot;
};
