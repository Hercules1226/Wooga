// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndingActor.generated.h"

UCLASS()
class WOOGA_API AEndingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* holo1;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* holo2;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* holo3;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* holo4;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* holo5;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* holo6;
};
