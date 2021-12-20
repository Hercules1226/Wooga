// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_ChangeFreeMove.generated.h"

UCLASS()
class WOOGA_API ASJ_ChangeFreeMove : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_ChangeFreeMove();

	UPROPERTY(EditAnywhere, Category = Change)
	class UBoxComponent* range;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPlayerIn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	class AVR_Player* player;

	UPROPERTY()
	class ASJ_WoogaGameModeBase* gameMode;

	UPROPERTY()
	class AMoveSpline* moveSpline;

	UPROPERTY()
	bool bisFreeMove;

	UPROPERTY()
	float curTime;
};
