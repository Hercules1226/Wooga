// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirePosition.generated.h"

UCLASS()
class WOOGA_API AFirePosition : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFirePosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, Category = Setting)
		class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = OutLine)
		class UStaticMeshComponent* outLine;

	UPROPERTY(EditAnywhere, Category = FX)
		class UParticleSystemComponent* FX;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		FVector grabOffset;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		class AFireRock* fireRock;

	UPROPERTY()
		class AFireRock2* fireRock2;

	UPROPERTY()
		class AReturnZone* returnZone;

	UPROPERTY()
		bool bisFire = false;

	UPROPERTY(EditAnywhere, Category = "Fire")
		class UParticleSystem* smokeFactory;

	UPROPERTY(EditAnywhere, Category = "Fire")
		class UParticleSystem* emberFactory;

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

	UPROPERTY()
		FVector startPoint;

	UPROPERTY()
	float outLineParam = 250;
};
