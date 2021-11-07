// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HandActorComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WOOGA_API UHandActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHandActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		class UVRHandAnimInstance* l_handAnim;
	UPROPERTY()
		class UVRHandAnimInstance* r_handAnim;
	UPROPERTY()
		class AVR_Player* player;

	UPROPERTY()
		float targetGripValueLeft = 0;
	UPROPERTY()
		float targetGripValueRight = 0;

	UPROPERTY(EditAnywhere, Category = HandAnimSettings)
		float gripSpeed = 20.f;
};
