// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_HowToGrabUI.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

void USJ_HowToGrabUI::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(OpenUI);
}

void USJ_HowToGrabUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	if (player->isClose == true)
	{
		Close();
	}
}

void USJ_HowToGrabUI::Close()
{
	PlayAnimation(CloseUI);
}
