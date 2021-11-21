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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

public:

	UPROPERTY()
		class AStick* stick;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterial* offMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterial* onMaterial;

	UPROPERTY()
		bool check1 = false;
	UPROPERTY()
		bool check2 = false;
	UPROPERTY()
		bool check3 = false;
	UPROPERTY()
		bool check4 = false;
};
