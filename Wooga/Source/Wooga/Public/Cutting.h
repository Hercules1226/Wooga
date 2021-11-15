// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cutting.generated.h"

UCLASS()
class WOOGA_API ACutting : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACutting();

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
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* handle;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* line;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UPhysicsConstraintComponent* constraint;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		class AFistAxe* fA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* onMaterialHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* onMaterialFA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* offMaterial;

	UPROPERTY()
		bool bisOverlabR = false;
	UPROPERTY()
		bool bisOverlabL = false;
	UPROPERTY()
		bool bisfinish = false;

	UPROPERTY()
		float handleX;
	UPROPERTY()
		float handleY;
	UPROPERTY()
		float handleZ;
};
