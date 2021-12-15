// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_RunDeer.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_RunDeer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_RunDeer();

	UPROPERTY(EditAnywhere, Category = Deer)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Deer)
	class USkeletalMeshComponent* deer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ASJ_Actor_DeerTurnAndDestroy* turnAndDestory;

	UPROPERTY()
	FVector me;

	UPROPERTY()
	FVector turnPoint;

	UPROPERTY()
	FVector diePoint;

	UPROPERTY()
	FVector dir;

	UPROPERTY()
	float speed = 500.0f;

	UPROPERTY()
	bool isTurn;

	UPROPERTY()
	bool isDestroy;

	void RunDeer();
};
