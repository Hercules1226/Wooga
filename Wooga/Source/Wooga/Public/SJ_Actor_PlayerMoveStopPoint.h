// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_PlayerMoveStopPoint.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_PlayerMoveStopPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_PlayerMoveStopPoint();

	UPROPERTY(EditAnywhere, Category = Point)
	class UBoxComponent* point;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class AVR_Player* player;
	UPROPERTY()
	class AMoveSpline* moveSpline;

	UFUNCTION()
	void PlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*  OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
