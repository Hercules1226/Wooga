// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SJ_PlayerWatchUI.generated.h"

/**
 *
 */
UCLASS()
class WOOGA_API USJ_PlayerWatchUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// ���� �߰�
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (BindWidget))
		class UImage* FireDiscoveryIcon;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* FireDiscoveryClear;

	// ä��
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (BindWidget))
		class UImage* CollectIcon;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* CollectClear;

	// �ָԵ���
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (BindWidget))
		class UImage* HandAxIcon;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* HandAxClear;

	// ���� ���
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (BindWidget))
		class UImage* FireUseIcon;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* FireUseClear;

	// �������
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (BindWidget))
		class UImage* SpearIcon;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* SpearClear;

	// ����
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (BindWidget))
		class UImage* HutIcon;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Animation", meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* HutClear;

	// ����� ������
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Image", meta = (BindWidget))
		class UProgressBar* hungryGaze;

	class AVR_Player* player;

	void FireDiscovery();
};
