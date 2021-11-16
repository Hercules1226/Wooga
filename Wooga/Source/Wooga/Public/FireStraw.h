// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireStraw.generated.h"

UCLASS()
class WOOGA_API AFireStraw : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireStraw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Settings)
		class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UPointLightComponent* pointLight;

	UPROPERTY(EditAnywhere, Category = OutLine)
		class UStaticMeshComponent* outLine;

	UPROPERTY(EditAnywhere, Category = "Fire")
		class UParticleSystem* smogFactory;

	UPROPERTY(EditAnywhere, Category = "Fire")
		class UParticleSystem* fireFactory;

	UPROPERTY()
		bool bisOverlab = false;
	UPROPERTY()
		bool bisSmog = false;
	UPROPERTY()
		bool bisFire = false;
	UPROPERTY()
		bool bisReadyFire = false;

	UPROPERTY()
		float smogCurrentTime = 0;
	UPROPERTY()
		float fireCurrentTime = 0;

	UPROPERTY()
		bool isClear;

	// sound
	UPROPERTY()
		const UObject* WorldContextObject;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* SoundBase;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* SoundBase2;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* SoundBase3;

	UPROPERTY()
		FVector location;
	UPROPERTY()
		FRotator rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class UAudioComponent* fireLoopSound;

	UPROPERTY()
		float VolumeMultiplier = 1.f;
	UPROPERTY()
		float PitchMultiplier = 1.f;
	UPROPERTY()
		float StartTime = 0.f;
	UPROPERTY()
		class USoundAttenuation* attenuationSettings;
	UPROPERTY()
		USoundConcurrency* ConcurrencySettings;
	UPROPERTY()
		bool bAutoDestroy = false;
	UPROPERTY()
		int32 overlabCount = 0;
};
