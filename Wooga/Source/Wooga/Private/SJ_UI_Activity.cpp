// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_UI_Activity.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"

void USJ_UI_Activity::NativeConstruct()
{
	Super::NativeConstruct();

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	PlayAnimation(OpenUI);
}

void USJ_UI_Activity::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (gameMode->bIsUIClose == true)
	{
		PlayAnimation(CloseUI);
	}
}
