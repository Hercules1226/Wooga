// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_UI_Hologram.h"
#include "SJ_WoogaGameModeBase.h"

void USJ_UI_Hologram::NativeConstruct()
{
	Super::NativeConstruct();

	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	// PlayAnimation(OpenUI);
}

void USJ_UI_Hologram::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	nextDelayTime += InDeltaTime;

	// ÁÖ¸Ôµµ³¢
	if (nextDelayTime >= 15.0f)
	{
		if (gameModeBase->flowState == EFlowState::CompleteHandAx)
		{
			PlayAnimation(CloseUI);

			nextDelayTime = 0;
		}
	}
	
}