// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_Bird.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_Bird : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_Bird();

	UPROPERTY(EditAnywhere, Category = Bird)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Bird)
	class UBoxComponent* destroyZone;

	UPROPERTY(EditAnywhere, Category = Bird)
	class USkeletalMeshComponent* bird;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	float animSpeed;

	UPROPERTY()
	bool isFly;

	UPROPERTY()
	float speed; 

	UPROPERTY()
	float currentTime;

	UFUNCTION()
	void OnBirdEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Fly();

};
