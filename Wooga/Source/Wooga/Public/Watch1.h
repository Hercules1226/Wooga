// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Watch1.generated.h"

UCLASS()
class WOOGA_API AWatch1 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWatch1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void WatchLookat();

	void Ending();

	UPROPERTY(EditAnywhere, Category = Setting)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* watch;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		FVector watchLoc;

	UPROPERTY()
		FRotator myRot;
	
	UPROPERTY()
		FVector dir;

	UPROPERTY()
		float speed = 10.f;

	UPROPERTY()
		float currentTime;

	UPROPERTY()
		bool bisEnd = false;

	UPROPERTY()
		bool bisStartFollow = true;

	// ending

	UPROPERTY()
		class AIconSpot* spot;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon1* icon1;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon1> icon1Factory;

	UPROPERTY()
	float endingCurrentTime;

	UPROPERTY()
		bool bisfinish = false;
};
