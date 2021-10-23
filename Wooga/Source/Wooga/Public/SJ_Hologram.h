// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Hologram.generated.h"

UCLASS()
class WOOGA_API ASJ_Hologram : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Hologram();

	UPROPERTY(VisibleAnywhere, Category = Hologram)
		class USceneComponent* rootComp;

	UPROPERTY(VisibleAnywhere, Category = Hologram)
		class UStaticMeshComponent* meshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AVR_Player* player;

	EHologramState holoState;
	void SetState(EHologramState state);
	EHologramState GetState();

	void TurnOnHologram();
	void PlayHologram();
	void TurnOffHologram();

	float createTime;
	float startParam;
	
	float playTime;
	UPROPERTY(EditAnywhere, Category = Time)
	float playChangeTime = 5.0f;

	float destroyTime;
	float destroyParam;

	UPROPERTY(EditAnywhere, Category = "FX")
	class UNiagaraSystem* destroyFX;
};
