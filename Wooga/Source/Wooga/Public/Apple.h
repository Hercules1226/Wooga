// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

class UNiagaraSystem;

UCLASS()
class WOOGA_API AApple : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AApple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Setting)
		class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMesh* mesh2;

	UPROPERTY(EditAnywhere, Category = Outline)
		class UStaticMeshComponent* outLine;

	// 소켓에 넣을떄 Offset 값을 조정
	UPROPERTY(EditAnywhere, Category = Setting)
		FVector grabOffset;

	UPROPERTY(EditAnywhere, Category = Setting)
		UNiagaraSystem* explosion;

	UPROPERTY()
		float currentTime;

	// sound
	UPROPERTY()
		const UObject* WorldContextObject;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* SoundBase;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* SoundBase2;

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
		bool bisgrab = false;
	UPROPERTY()
		bool bisEat = false;
	UPROPERTY()
		int32 overlabCount = 0;
	UPROPERTY()
		bool bisEatComplete;
};
