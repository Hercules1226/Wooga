// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireEvent.generated.h"

UCLASS()
class WOOGA_API AFireEvent : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* planeComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class USkeletalMeshComponent* skelComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class AVR_Player* player;

		UPROPERTY()
		class AWatch1* watch;
};
