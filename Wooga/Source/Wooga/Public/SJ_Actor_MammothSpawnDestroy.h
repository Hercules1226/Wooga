// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_MammothSpawnDestroy.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_MammothSpawnDestroy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_MammothSpawnDestroy();

	UPROPERTY(EditAnywhere, Category = Root)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Range)
	class UBoxComponent* spawnRange;

	UPROPERTY(EditAnywhere, Category = Range)
	class UBoxComponent* destroyRange;

	UPROPERTY(EditAnywhere, Category = Mammoth)
	class USkeletalMeshComponent* mammoth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Speed)
	float speed = 300.0f;

	UFUNCTION()
	void TriggerIn( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
