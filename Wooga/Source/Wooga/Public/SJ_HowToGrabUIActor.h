// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_HowToGrabUIActor.generated.h"

UCLASS()
class WOOGA_API ASJ_HowToGrabUIActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASJ_HowToGrabUIActor();

	UPROPERTY(EditAnywhere, Category = UI)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = UI)
		class UStaticMeshComponent* plane;

	UPROPERTY(EditAnywhere, Category = UI)
		class UWidgetComponent* widgetComp;

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

};
