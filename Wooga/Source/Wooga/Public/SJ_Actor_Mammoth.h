// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_Mammoth.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_Mammoth : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_Mammoth();

	UPROPERTY(EditAnywhere, Category = Collider)
	class UBoxComponent* rootBox;

	UPROPERTY(EditAnywhere, Category = Mammoth)
	class USkeletalMeshComponent* mammoth;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ASJ_Actor_MammothSpawnDestroy* range;

	UPROPERTY(EditAnywhere, Category = Speed)
	float speed = 300.0f;

	UPROPERTY(EditAnywhere, Category = Mammoth)
	TSubclassOf<class UCameraShakeBase> mammothCameraShake;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* footStepSound;

	UPROPERTY()
	float playTime;
};
