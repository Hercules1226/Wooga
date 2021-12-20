// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LastHouse.generated.h"

UCLASS()
class WOOGA_API ALastHouse : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALastHouse();

	UPROPERTY(EditAnywhere, Category = Data)
		TArray<UStaticMeshComponent*> stickArray;

	UPROPERTY(EditAnywhere, Category = Data)
		int32 stickCount = 22;

	UPROPERTY()
		int32 creatCount = 0;
	/*UPROPERTY(EditAnywhere, Category=Data)
	TSubclassOf<AActor> subEnemy;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void CreateStick();

	UPROPERTY(EditAnywhere, Category = Settings)
		class USceneComponent* sceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UStaticMeshComponent* tree1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UStaticMeshComponent* tree2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UStaticMeshComponent* tree3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UStaticMeshComponent* tree4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UStaticMeshComponent* base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UStaticMeshComponent* complete;

public:


	UPROPERTY()
		class AStick* stick;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterial* offMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterial* onMaterial;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* overlabSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* sound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* createHouse;

	UPROPERTY()
		float currentTime = 0;

	UPROPERTY()
		float currentTime2 = 0;

	UPROPERTY()
		float baseTime = 0.5f;

	UPROPERTY()
		float completeTime = 6.f;

	UPROPERTY()
		float disTime;

	UPROPERTY()
		float blend;

	UPROPERTY()
		bool check1 = true;
	UPROPERTY()
		bool check2 = false;
	UPROPERTY()
		bool check3 = false;
	UPROPERTY()
		bool check4 = false;

	UPROPERTY()
		bool bisfinish = false;

	UPROPERTY()
		bool bisClear = false;

	UPROPERTY()
		bool bisFadeStart = false;

	UPROPERTY()
		bool isUIDown;

	UPROPERTY()
		bool bisAttachStart;

	UPROPERTY()
		bool lastSoundEnd = false;
};
