// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_CatchFish.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_CatchFish : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASJ_Actor_CatchFish();

	UPROPERTY(EditAnywhere, Category = Fish)
		class USkeletalMeshComponent* fish;

	UPROPERTY(EditAnywhere, Category = fish)
		class USkeletalMeshComponent* outlineFish;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		class USJ_CatchFishAnimInstance* catchFishAnimInst;

	UPROPERTY(EditAnywhere, Category = "Explosion")
		class UParticleSystem* explosionFactory;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* explosionSound;

	UPROPERTY()
		bool isAttacked;

	UPROPERTY()
		bool biscatch = true;

		UPROPERTY()
		class ACable* sumjji;
};
