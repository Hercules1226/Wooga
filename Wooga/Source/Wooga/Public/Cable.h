// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cable.generated.h"

UCLASS()
class WOOGA_API ACable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* stickComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* cableComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class USplineComponent* splineComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* rockComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* outLine;

	UPROPERTY(EditAnywhere, Category = Settings)
		class USkeletalMeshComponent* fish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* onMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* offMaterial;

	UPROPERTY()
		class AString* string;

	UPROPERTY()
		class ASJ_Actor_CatchFish* catchFish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterial* welldone;

	UPROPERTY()
		float currentTime;

	UPROPERTY()
		float currentTime2;

	UPROPERTY()
		float niaCreateTime;

	UPROPERTY()
		class ASumjjiRock* sumjjiRock;

	UPROPERTY()
		class UNiagaraComponent* nia;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* eatSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* fireSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* clearSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* padakSound;

	UPROPERTY(EditAnywhere, Category = "Explosion")
		class UParticleSystem* explosionFactory;

	UPROPERTY(EditAnywhere, Category = Setting)
		FVector grabOffset;

	UPROPERTY()
		bool bisSumjjiRock = false;

	UPROPERTY()
		bool biscatch = false;

	UPROPERTY()
		bool bisOverlab = false;

	UPROPERTY()
		bool bisWelldone = false;

	UPROPERTY()
		bool bIsConnect;

	UPROPERTY()
		bool bIsTie;

	UPROPERTY()
		bool bIsConnectRock = false;

	UPROPERTY()
		bool bisEat = false;

	UPROPERTY()
		bool bisfire = true;

	UPROPERTY()
		bool niaStart = false;

	UPROPERTY()
		bool playPadakSound = false;
};
