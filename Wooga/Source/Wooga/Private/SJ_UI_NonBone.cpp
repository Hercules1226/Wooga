// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_UI_NonBone.h"

void USJ_UI_NonBone::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(OpenUI);
}

void USJ_UI_NonBone::CloseAnimation()
{
	PlayAnimation(CloseUI);
}
