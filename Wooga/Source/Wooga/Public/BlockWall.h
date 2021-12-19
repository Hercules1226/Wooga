// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockWall.generated.h"

UCLASS()
class WOOGA_API ABlockWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		FVector wallPos;

	UPROPERTY()
		FVector playerPos;
};
