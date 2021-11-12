// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ÇöÀç ÄÃ·¯
	UPROPERTY()
	FLinearColor curDirColor;
	UPROPERTY()
	FLinearColor curSunColor;

	// ³· ÄÃ·¯
	UPROPERTY()
	FLinearColor dayDirColor = FLinearColor(255, 216, 118);
	UPROPERTY()
	FLinearColor daySunColor = FLinearColor(248, 229, 197);

	// ¹ã ÄÃ·¯
	UPROPERTY()
	FLinearColor nightDirColor = FLinearColor(74, 126, 155);
	UPROPERTY()
	FLinearColor nightSunColor = FLinearColor(35, 39, 49);

};
