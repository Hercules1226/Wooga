// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_KnowledgePoint.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_KnowledgePoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASJ_Actor_KnowledgePoint();

	UPROPERTY(EditAnywhere, Category = KnowledegePoint)
		class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = KnowledegePoint)
		class USkeletalMeshComponent* skeletalMesh;

	UPROPERTY(EditAnywhere, Category = KnowledegePoint)
		class UStaticMeshComponent* meshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class AMoveSpline* moveSpline;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		class AWatch1* watch1;

	UPROPERTY()
		class AWatch2* watch2;

	UPROPERTY()
		class AWatch3* watch3;

	UPROPERTY()
		class AWatch4* watch4;

	UPROPERTY()
		class AWatch5* watch5;

	UPROPERTY()
		class AWatch6* watch6;

	UPROPERTY()
		FVector me;
	UPROPERTY()
		FVector target;
	UPROPERTY()
		FVector dir;
	UPROPERTY()
		FVector p;

	UPROPERTY()
		float speed = 100;

	/*UPROPERTY()
		bool bisTouch1;

	UPROPERTY()
		bool bisTouch2;

	UPROPERTY()
		bool bisTouch3;

	UPROPERTY()
		bool bisTouch4;

	UPROPERTY()
		bool bisTouch5;

	UPROPERTY()
		bool bisTouch6;*/

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;

	UPROPERTY(EditAnywhere,Category = Sound)
	class USoundBase* swingSound;
};
