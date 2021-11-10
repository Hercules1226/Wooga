// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_GoToGuideLine.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_GoToGuideLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_GoToGuideLine();

	UPROPERTY(EditAnywhere, Category = UI)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = UI)
		class UWidgetComponent* informUI;

	UPROPERTY(EditAnywhere, Category = UI)
		class UBoxComponent* range;

	UPROPERTY(EditAnywhere, Category = FootHold)
	class UStaticMeshComponent* footHold;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void  RangeIn(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	class ASJ_WoogaGameModeBase* gameModeBase;

	class AVR_Player* player;

	UPROPERTY()
	bool isTrigger;

	UPROPERTY()
	float changeTime;
};
