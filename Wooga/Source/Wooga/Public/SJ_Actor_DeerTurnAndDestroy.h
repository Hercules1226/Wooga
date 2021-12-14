// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_DeerTurnAndDestroy.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_DeerTurnAndDestroy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_DeerTurnAndDestroy();

	UPROPERTY(EditAnywhere, Category = TurnAndDestroy)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = TurnAndDestroy)
		class UBoxComponent* turnPoint;

	UPROPERTY(EditAnywhere, Category = TurnAndDestroy)
		class UBoxComponent* destroyPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTurnPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDestroyPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
