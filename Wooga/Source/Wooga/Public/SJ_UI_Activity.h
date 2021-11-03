// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SJ_UI_Activity.generated.h"

/**
 *
 */
UCLASS()
class WOOGA_API USJ_UI_Activity : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
		class ASJ_WoogaGameModeBase* gameMode;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* OpenUI;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* CloseUI;
};
