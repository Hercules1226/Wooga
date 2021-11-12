// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cable.generated.h"

UCLASS()
class WOOGA_API ACable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* stickComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* cableComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class USplineComponent* splineComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* rockComp;

	UPROPERTY(EditAnywhere, Category = Settings)
		class UStaticMeshComponent* handComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* onMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)
		class UMaterialInstance* offMaterial;

	UPROPERTY()
		class UNiagaraComponent* nia;

	UPROPERTY(EditAnywhere, Category = Setting)
		FVector grabOffset;
};
