// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SJ_IntroGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WOOGA_API ASJ_IntroGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASJ_IntroGameModeBase();

	virtual void BeginPlay() override;

	FTimerHandle introSoundTimer;
	FTimerHandle moveLevelTimer;
	FTimerHandle fadeOutTimer;

	void IntroSound();
	void MoveLevel();
	void FadeOutFunc();
	
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* introNarration;
};
