// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SJ_EscapeFishAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WOOGA_API USJ_EscapeFishAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimInstance")
		bool isRun;
};
