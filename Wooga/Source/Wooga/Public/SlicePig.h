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

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class UStaticMeshComponent* pigHead;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class UStaticMeshComponent* top;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class UStaticMeshComponent* bottom;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class UStaticMeshComponent* inside;

	UPROPERTY()
		ACutting* cutting;

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

};
