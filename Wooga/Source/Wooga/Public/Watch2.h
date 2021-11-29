// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Watch2.generated.h"

UCLASS()
class WOOGA_API AWatch2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWatch2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setting)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* watch;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		float currentTime;

	UPROPERTY()
		bool bisEnd = false;

	// ending

	UPROPERTY()
		class AIconSpot* spot;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AIcon2* icon2;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyFactory")
		TSubclassOf<class AIcon2> icon2Factory;

	UPROPERTY()
		float endingCurrentTime;

	UPROPERTY()
		bool bisfinish = false;

	UPROPERTY()
	FRotator curRot;

	UPROPERTY()
	FRotator targetrot;

	UPROPERTY()
	FVector dir;
};
