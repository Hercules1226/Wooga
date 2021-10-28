// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_HowToManipulate.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_HowToManipulate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_HowToManipulate();

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

	class AVR_Player* player;
};
