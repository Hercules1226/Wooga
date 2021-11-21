// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Icon4.generated.h"

UCLASS()
class WOOGA_API AIcon4 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIcon4();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* icon;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* holo;

	UPROPERTY()
		class AIconSpot* spot;
};
