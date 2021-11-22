// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_UI_Hologram.h"
#include "SJ_WoogaGameModeBase.h"

void USJ_UI_Hologram::NativeConstruct()
{
	Super::NativeConstruct();

	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	PlayAnimation(OpenUI);
}

void USJ_UI_Hologram::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	nextDelayTime += InDeltaTime;

	if (gameModeBase->flowState == EFlowState::Firing || gameModeBase->flowState == EFlowState::CompleteFireDiscovery)
	{
		if (nextDelayTime >= 14.0f)
		{
			PlayAnimation(CloseUI);

			nextDelayTime = 0;
		}
	}
	else if (gameModeBase->flowState == EFlowState::CollectAndEat || gameModeBase->flowState == EFlowState::CompleteCollect)
	{
		if (nextDelayTime >= 12.0f)
		{
			PlayAnimation(CloseUI);

			nextDelayTime = 0;
		}
	}
	else if (gameModeBase->flowState == EFlowState::CompleteHandAx)
	{
		if (nextDelayTime >= 14.0f)
		{
			PlayAnimation(CloseUI);

			nextDelayTime = 0;
		}
	}
	else if (gameModeBase->flowState == EFlowState::CompleteFireUse)
	{
		if (nextDelayTime >= 23.0f)
		{
			PlayAnimation(CloseUI);

			nextDelayTime = 0;
		}
	}
	else if (gameModeBase->flowState == EFlowState::CompleteSpear)
	{
		if (nextDelayTime >= 15.0f)
		{
			PlayAnimation(CloseUI);

			nextDelayTime = 0;
		}
	}
	else if(gameModeBase->flowState == EFlowState::CompleteHut)
	{
		if (nextDelayTime >= 20.0f)
		{
			PlayAnimation(CloseUI);

			nextDelayTime = 0;
		}
	}
}