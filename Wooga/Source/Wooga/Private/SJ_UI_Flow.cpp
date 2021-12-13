// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_UI_Flow.h"
#include "SJ_Actor_HowToFlow.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>


void USJ_UI_Flow::NativeConstruct()
{
	Super::NativeConstruct();

	howToFlow = Cast<ASJ_Actor_HowToFlow>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_HowToFlow::StaticClass()));

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	PlayAnimation(OpenUI);
}

void USJ_UI_Flow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	currentTime += InDeltaTime;

	if (currentTime >= howToFlow->playTime + 1.0f)
	{
		if (player->isClose == true)
		{
			currentTime = 0;
			PlayAnimation(CloseUI);
		}
	}
}

void USJ_UI_Flow::NextAnimation()
{
	PlayAnimation(NextUI);
}

