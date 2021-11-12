// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EFlowState : uint8
{
	InGame,
	ManipulateUI,
	HowToGrabActorUI,
	// ����  �߰�
	FireDiscoveryTitle,
	HowToFireUI,
	HowToFireUINext,
	Firing,
	CompleteFireDiscovery,
	InformWatch,
	GoToCollectCourse,
	// ä��
	CollectTitle,
	HowToCollectActorUI,
	CollectAndEat,
	CompleteCollect,
	GoToFistAxCourse,
	// ���(�ָԵ���)
	HandAxTitle,
	SeeMammoth,
	GrabHandAx,
	RunBoar,
	HitBoar,
	MakeHandAx,
	IndirectnessHit,
	DirectlyHit,
	CompleteHandAx,
	// ���� Ȱ��
	CuttingPig,
	GoToFireUse
};

UENUM(BlueprintType)
enum class EHologramState : uint8
{
	TurnOnHologram,
	PlayHologram,
	TurnOffHologram
};

UENUM(BlueprintType)
enum class EBlinkState : uint8
{
	OnOpacity,
	PlayOpacity,
	OffOpacity
};

UENUM(BlueprintType)
enum class EBoarState : uint8
{
	Run,
	SlowMotion,
	Hit,
	Die
};