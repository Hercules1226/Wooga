// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireRock.generated.h"

UCLASS()
class WOOGA_API AFireRock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireRock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = Outline)
		class UStaticMeshComponent* outLine;

	UPROPERTY()
		float currentTime;

	UPROPERTY()
		class AFireRock* me;

	UPROPERTY()
		class AFireRock2* fireRock2;

	UPROPERTY()
		class AVR_Player* player;

	// 소켓에 넣을떄 Offset 값을 조정
	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		FVector grabOffset;

	// 넉벡 종료지점
	UPROPERTY()
		FVector knockbackPos;

	UPROPERTY()
		FVector returnKnockbackPos;

	UPROPERTY()
		FVector myPos;

	UPROPERTY()
		bool bisOverlab = false;

	UPROPERTY(EditAnywhere, Category = "Explosion")
		class UParticleSystem* explosionFactory;

	// sound
	UPROPERTY()
		const UObject* WorldContextObject;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* SoundBase;

	UPROPERTY()
		FVector location;
	UPROPERTY()
		FRotator rotation;

	UPROPERTY()
		float VolumeMultiplier = 1.f;
	UPROPERTY()
		float PitchMultiplier = 1.f;
	UPROPERTY()
		float StartTime = 0.f;
	UPROPERTY()
		class USoundAttenuation* AttenuationSettings;
	UPROPERTY()
		USoundConcurrency* ConcurrencySettings;
	UPROPERTY()
		bool bAutoDestroy = false;
	UPROPERTY()
		int32 overlabCount = 0;
};
