// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_BoarLeapFXRange.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_BoarLeapFXRange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_BoarLeapFXRange();
	UPROPERTY(EditAnywhere, Category = Range)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = Range)
	class UBoxComponent* range;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ASJ_Character_Boar* boar;

	UFUNCTION()
	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexs);

	UPROPERTY(EditAnywhere, Category = FX)
	class UParticleSystem* leapParticle;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* leapSound;

};
