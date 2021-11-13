// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tomahowk.generated.h"

UCLASS()
class WOOGA_API ATomahowk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATomahowk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* medium;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* welldone;

	UPROPERTY()
		class AFireStraw* fireStraw;

	UPROPERTY()
		bool bisOverlab = false;

	UPROPERTY()
		float currentTime;
};
