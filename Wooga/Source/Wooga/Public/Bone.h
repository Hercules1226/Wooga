// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bone.generated.h"

UCLASS()
class WOOGA_API ABone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = Setting)
		FVector grabOffset;
};
