// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SumjjiRock.generated.h"

UCLASS()
class WOOGA_API ASumjjiRock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASumjjiRock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UBoxComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* sumjji;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* rock1;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* rock2;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* rock3;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* rock4;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* outLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* onMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* offMaterial;

public:
	// 소켓에 넣을떄 Offset 값을 조정
	UPROPERTY(EditAnywhere, Category = Settings)
		FVector grabOffset;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		class ATomahowk* bone;

	UPROPERTY()
		float currentTime;

	// 넉벡 종료지점
	UPROPERTY()
		FVector knockbackPos;

	UPROPERTY()
		FVector returnKnockbackPos;

	UPROPERTY()
		FVector myPos;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* Sound;

public:
	UPROPERTY()
		bool bisOverlab = false;

	UPROPERTY()
		bool bisRock2 = false;
	UPROPERTY()
		bool bisRock3 = false;
	UPROPERTY()
		bool bisRock4 = false;
	UPROPERTY()
		bool bisRockFin = false;
};
