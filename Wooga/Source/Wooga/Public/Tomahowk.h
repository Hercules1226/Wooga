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
		class UBoxComponent* meshComp;
	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp1;
	UPROPERTY(EditAnywhere, Category = Setting)
		class UStaticMeshComponent* meshComp4;

	UPROPERTY(EditAnywhere, Category = Setting)
	class UStaticMeshComponent* meatOutline;
	UPROPERTY(EditAnywhere, Category = Setting)
	class UStaticMeshComponent* boneOutline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* medium;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* welldone;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* bakeSound;

	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* sound;

	UPROPERTY()
		class AFireStraw* fireStraw;

	/*UPROPERTY()
		class AReturnZone* returnZone;*/

	UPROPERTY()
		float currentTime;

	UPROPERTY(EditAnywhere, Category = Setting)
		FVector grabOffset;

	UPROPERTY()
		float blend;

	UPROPERTY()
		float disTime;

	UPROPERTY()
		bool bisOverlab = false;

	UPROPERTY()
		bool bisWelldone = false;

	UPROPERTY()
		bool bisBone = false;

	UPROPERTY()
		bool bCanBake = false;

	UPROPERTY()
		bool bisBake = false;

	UPROPERTY()
		bool bcanEat = false;

	UPROPERTY()
		bool bisEat = false;

	UPROPERTY()
		bool bisfk = false;

	UPROPERTY()
	class AMoveSpline* moveSpline;

	UPROPERTY()
	class ASJ_NonGrabBoneUI* grabUI;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ASJ_NonGrabBoneUI> bpGrabUI;
};
