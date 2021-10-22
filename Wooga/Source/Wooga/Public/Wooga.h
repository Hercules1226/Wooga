// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EFlowState : uint8
{
	// ����  �߰�
	HowToGrabActorUI,
	HowToFireUI,
	Firing,
	CompleteFireDiscovery,
	InformWatch,
	GoToCollectCourse,
	// ä��
	HowToCollectActorUI,
	CollectAndEat,
	CompleteCollect,
	GoToFistAxCourse
};

UENUM(BlueprintType)
enum class EHologramState : uint8
{
	TurnOnHologram,
	PlayHologram,
	TurnOffHologram
};

