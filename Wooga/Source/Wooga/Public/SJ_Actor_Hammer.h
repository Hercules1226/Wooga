// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_Hammer.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_Hammer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_Hammer();

	UPROPERTY(	EditAnywhere, Category = Hammer)
	class UStaticMeshComponent* hammer;

	UPROPERTY()
	class ASJ_Character_Boar* boar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
