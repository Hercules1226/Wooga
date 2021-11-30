// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow1.generated.h"

UCLASS()
class WOOGA_API AArrow1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp;

	UPROPERTY()
		float pm = 1;

	UPROPERTY()
		FVector dir;

	UPROPERTY()
		float currentTime;

	UPROPERTY()
		float moveSpeed = 50.f;

	// È¸Àü

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		FVector rotDir;

	UPROPERTY()
		FRotator targetrot;

	UPROPERTY()
		FRotator curRot;

	UPROPERTY()
		float targetRotYaw;

	UPROPERTY()
		bool arrowOn = false;

};
