// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DecalTest.generated.h"

UCLASS()
class WOOGA_API ADecalTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecalTest();

	UPROPERTY(EditAnywhere, Category = Decal)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Decal)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = Decal)
	class UDecalComponent* decal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	bool isTrig;
};
