// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "String_nia.generated.h"

UCLASS()
class WOOGA_API AString_nia : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AString_nia();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UNiagaraComponent* nia;

	UPROPERTY()
		class ACable* cable;
};
