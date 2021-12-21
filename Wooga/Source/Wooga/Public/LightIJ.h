// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "GameFramework/Actor.h"
#include "LightIJ.generated.h"

UCLASS()
class WOOGA_API ALightIJ : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightIJ();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		AActor* sun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
		ADirectionalLight* lightSource;

	UPROPERTY(EditAnywhere, Category = "Sky")
		float turnRate;
};
