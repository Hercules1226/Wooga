// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_LevelLight.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_LevelLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_LevelLight();

	UPROPERTY(EditAnywhere, Category = Root)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Light)
	class UDirectionalLightComponent* directLight;

	UPROPERTY(EditAnywhere, Category = Light)
	class UDirectionalLightComponent* sun;

	UPROPERTY(EditAnywhere, Category = Light)
	class USkyLightComponent* skyLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
	class UStaticMeshComponent* skySphere;

	UPROPERTY(EditAnywhere, Category = Light)
	class UPostProcessComponent* levelPost;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ELightState lightState;
	ELightState GetState();
	void SetState(ELightState state);

	void Stay();
	void Day();
	void Night();

	// 현재 컬러
	UPROPERTY()
	FLinearColor curDirColor = FLinearColor(0.068478f, 0.208637f, 0.327778f);
	UPROPERTY()
	FLinearColor curSunColor = FLinearColor(0.016807f, 0.020289f, 0.030713f);

	// 낮 컬러
	UPROPERTY()
	// FLinearColor dayDirColor = FLinearColor(194, 144, 169);
	FLinearColor dayDirColor = FLinearColor(0.64448f, 0.799103f, 1.0f);
	//IJ
	UPROPERTY()
	// FLinearColor daySunColor = FLinearColor(255, 211, 170);
	//IJ
	FLinearColor daySunColor = FLinearColor(1.0f, 0.955973f, 0.822786f);

	UPROPERTY(EditAnywhere, Category = Setting)
	struct FPostProcessSettings dayParam;


	// 밤 컬러
	UPROPERTY()
	FLinearColor nightDirColor = FLinearColor(0.068478f, 0.208637f, 0.327778f);
	UPROPERTY()
	FLinearColor nightSunColor = FLinearColor(0.016807f, 0.020289f, 0.030713f);

	// 변환 변수
	UPROPERTY()
	float changeTIme;

	UPROPERTY()
	bool isDay;
	UPROPERTY()
	bool isNight;

	FVector4 changeParam2;

};
