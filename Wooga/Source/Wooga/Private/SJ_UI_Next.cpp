// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_UI_Next.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Image.h>

void USJ_UI_Next::NativeConstruct()
{
	Super::NativeConstruct();

}

void USJ_UI_Next::OpenAnimation()
{
	PlayAnimation(OpenUI);
}

void USJ_UI_Next::CloseAnimation()
{
	PlayAnimation(CloseUI);
}
