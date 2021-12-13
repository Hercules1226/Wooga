// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveSpline.generated.h"

UCLASS()
class WOOGA_API AMoveSpline : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMoveSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "SplineComtroller")
		USceneComponent* root;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "SplineComtroller")
		class USplineComponent* spline;

	UPROPERTY(EditDefaultsOnly, Category = "SplineController")
		TSubclassOf<class AActor> actorToMoveClass;

	class AActor* actorToMove;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SplineController")
		float totalPathTimeController;

	UPROPERTY(EditDefaultsOnly, Category = "SplineController")
		bool bSplineInLoop;

	UPROPERTY()
		bool bcanMoveActor;

	UPROPERTY()
		float startTime;

	UPROPERTY()
		float speed;

	UPROPERTY()
		float curTime = 0.f;

	UPROPERTY()
		float moveTime;

	UPROPERTY()
		float distance;

	UPROPERTY()
		float distanceRot;

	UPROPERTY()
		float currentSplineTime;

	UPROPERTY()
		float currentSplineTimeRot;

	UPROPERTY()
		bool timeOn = true;
};
