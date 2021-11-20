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

		void OnOpacity();
		void PlayOpacity();
		void OffOpacity();

		UPROPERTY(VisibleAnywhere, Category = knowledge)
		float knowledgePoint;

		UPROPERTY()
		bool isKnowledgeIn;

		UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;

		UPROPERTY(EditAnywhere, Category = Material)
		class UMaterial* watchOneMaterial;

		UPROPERTY()
		float playTime;
};
