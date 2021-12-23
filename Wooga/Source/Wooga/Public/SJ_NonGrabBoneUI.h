// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_NonGrabBoneUI.generated.h"

UCLASS()
class WOOGA_API ASJ_NonGrabBoneUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_NonGrabBoneUI();

	UPROPERTY(EditAnywhere, Category = UI)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = UI)
	class UWidgetComponent* widgetComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class AVR_Player* player;

	UPROPERTY()
	class USJ_UI_NonBone* nonBoneUI;

	UPROPERTY()
	float uiDownTime;

	UPROPERTY()
	bool bisUIDown;

};
