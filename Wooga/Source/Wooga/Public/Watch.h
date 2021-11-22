// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "Watch.generated.h"

UCLASS()
class WOOGA_API AWatch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWatch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EBlinkState blinkFlow;
	EBlinkState GetState();
	void SetState(EBlinkState state);

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* rootComp;
	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* watch;
	UPROPERTY(EditAnywhere, Category = Settings)
		class AVR_Player* player;

	UFUNCTION()
		void InKnowledgePoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Blink();
	void UnBlink();
	void Idle();

	UPROPERTY(VisibleAnywhere, Category = knowledge)
		float knowledgePoint;

	UPROPERTY()
		bool isKnowledgeIn;

	UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;

	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInstance* watchOneMaterial;

	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInstance* watchTwoMaterial;

	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInstance* watchThreeMaterial;

	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInstance* watchFourMaterial;

	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInstance* watchFiveMaterial;

	UPROPERTY(EditAnywhere, Category = Material)
		class UMaterialInstance* watchSixMaterial;


	UPROPERTY()
		float playTime;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon1* icon1;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon2* icon2;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon3* icon3;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon4* icon4;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon5* icon5;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon6* icon6;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon1> icon1Factory;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon2> Icon2Factory;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon3> Icon3Factory;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon4> Icon4Factory;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon5> Icon5Factory;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon6> Icon6Factory;
	UPROPERTY()
		bool bisEnd = false;
};
