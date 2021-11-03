// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_UI_SystemUI.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"


void USJ_UI_SystemUI::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	PlayAnimation(OpenUI);
}

void USJ_UI_SystemUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (player->isClose == true)
	{
		PlayAnimation(CloseUI);
	}
}