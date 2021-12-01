// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SJ_UI_Next.generated.h"

/**
 * 
 */
UCLASS()
class WOOGA_API USJ_UI_Next : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	class AVR_Player* player;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* OpenUI;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* CloseUI;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayNextUIAnimation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StopNextUIAnimation();

		void AnimPlay();
		UPROPERTY()
		float loopTime;
};
