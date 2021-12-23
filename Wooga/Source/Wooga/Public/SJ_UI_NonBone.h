// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SJ_UI_NonBone.generated.h"

/**
 * 
 */
UCLASS()
class WOOGA_API USJ_UI_NonBone : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* OpenUI;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* CloseUI;

		void CloseAnimation();
};
