// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_HitBoarUI.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_HitBoarUI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_HitBoarUI();

	UPROPERTY(VisibleDefaultsOnly, Category = Controller)
		class USceneComponent* rootComp;

	UPROPERTY()
		class UStaticMeshComponent* plane;

	UPROPERTY(EditAnywhere, Category = UI)
		class UWidgetComponent* hitBoarUI;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ASJ_Character_Boar* boar;
};
