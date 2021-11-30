// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlicePig.generated.h"

UCLASS()
class WOOGA_API ASlicePig : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASlicePig();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* pigHead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* top;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* bottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UDecalComponent* decal1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UDecalComponent* decal2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UDecalComponent* decal3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UDecalComponent* decal4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UDecalComponent* decal5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* decalCollision1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* decalCollision2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* decalCollision3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* decalCollision4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* decalCollision5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UMaterialInstance* onMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UMaterialInstance* decalMaterial;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* sound;

	UPROPERTY()
		float blend;

	UPROPERTY()
		float disTime;

	UPROPERTY()
		class ACutting* cutting;

	UPROPERTY()
		FVector topPos;

	UPROPERTY()
		FVector bottomPos;

	UPROPERTY()
		FVector targetTopPos;

	UPROPERTY()
		FVector targetBottomPos;

	UPROPERTY()
		FRotator topRot;

	UPROPERTY()
		FRotator bottomRot;

	UPROPERTY()
		FRotator targetTopRot;

	UPROPERTY()
		FRotator targetBottomRot;

	UPROPERTY()
		bool sound1 = true;

	UPROPERTY()
		bool sound2 = false;

	UPROPERTY()
		bool sound3 = false;

	UPROPERTY()
		bool sound4 = false;

	UPROPERTY()
		bool sound5 = false;
};
