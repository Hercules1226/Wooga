// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_EscapeFish.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_EscapeFish : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_EscapeFish();

	UPROPERTY(EditAnywhere, Category = Fish)
	class USceneComponent* root;

	UPROPERTY(EditAnywhere, Category = Fish)
		class USkeletalMeshComponent* fish;

	UPROPERTY()
	class USJ_EscapeFishAnimInstance* escapeFishAnimInst;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ASJ_Actor_CatchFish* catchFish;

	UPROPERTY(EditAnywhere, Category = Speed)
	float speed = 500;

	UPROPERTY()
	float destroyTime;
};
