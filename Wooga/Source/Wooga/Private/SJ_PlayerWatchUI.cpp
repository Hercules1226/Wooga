// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_PlayerWatchUI.h"
#include <Components/ProgressBar.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"

void USJ_PlayerWatchUI::NativeConstruct()
{
	Super::NativeConstruct();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	hungryGaze->SetPercent(0.45);
}

void USJ_PlayerWatchUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (player->knowledgePoint == 1 && player->isPlayAnim == true)
	{
		player->isPlayAnim = false;
		PlayAnimation(FireDiscoveryClear);
	}
	else if (player->knowledgePoint == 2 && player->isPlayAnim == true)
	{
		player->isPlayAnim = false;
		PlayAnimation(CollectClear);
	}
	else if (player->knowledgePoint == 3 && player->isPlayAnim == true)
	{
		player->isPlayAnim = false;
		PlayAnimation(HandAxClear);
	}

	if (gameMode->flowState == EFlowState::GoToCollectCourse)
	{
		gazeTime += InDeltaTime;
		if (gazeTime < 1.0f)
		{
			gazePer = FMath::Lerp(0.45f, 0.2f, gazeTime * 0.3);

			hungryGaze->SetPercent(gazePer);
		}
	}
}

void USJ_PlayerWatchUI::FireDiscovery()
{
	PlayAnimation(FireDiscoveryClear);
}
