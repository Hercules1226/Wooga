// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_MakeRange.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_MakeRange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_MakeRange();

	UPROPERTY(EditAnywhere, Category = Range)
	class UBoxComponent* range;

	UPROPERTY(EditAnywhere, Category = Range)
	class UStaticMeshComponent* footStep;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ASJ_WoogaGameModeBase* gameMode;

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	class AVR_Player* player;

	UPROPERTY()
	bool isPlayerIn;

	UPROPERTY()
	float returnTime;
};
