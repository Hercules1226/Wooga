// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_Hologram.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_Hologram : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_Hologram();

	UPROPERTY(EditAnywhere, Category = Hologram)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Hologram)
	class UStaticMeshComponent* plane;

	UPROPERTY(EditAnywhere, Category = Hologram)
	class UWidgetComponent* handAxHologram;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ASJ_WoogaGameModeBase* gameModeBase;

};
