// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SliceMeat.generated.h"

UCLASS()
class WOOGA_API ASliceMeat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASliceMeat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* front;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UStaticMeshComponent* back;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setting)
		class UMaterialInstance* onMaterial;

	UPROPERTY()
		float blend;

	UPROPERTY()
		float disTime;

	UPROPERTY()
		class ACutting2* cutting2;

	UPROPERTY()
		FVector frontPos;

	UPROPERTY()
		FVector backPos;

	UPROPERTY()
		FVector targetFrontPos;

	UPROPERTY()
		FVector targetBackPos;

	UPROPERTY()
		FRotator frontRot;

	UPROPERTY()
		FRotator backRot;

	UPROPERTY()
		FRotator targetFrontRot;

	UPROPERTY()
		FRotator targetBackRot;
};
