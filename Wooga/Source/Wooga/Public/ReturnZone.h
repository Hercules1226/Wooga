// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReturnZone.generated.h"

UCLASS()
class WOOGA_API AReturnZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReturnZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = PickUPSettings)
		class UStaticMeshComponent* meshComp;
};
