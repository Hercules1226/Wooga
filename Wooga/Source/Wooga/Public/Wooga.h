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
	GoToFireUse,
	FireUseTitle,
	FiringTwo,
	CookMeat,
	EatMeat,
	CompleteFireUse,
	GoToSpear,
	// �������
	SpearTitle,
	MakeSpear,
	TakeRock,
	ConnectSpear,
	TieSpear,
	CompleteSpear,
	HuntFish,
	CatchFish,
	GoToCookFish,
	CookFish,
	EatFish
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
	Idle,
	Blink,
	UnBlink
};

UENUM(BlueprintType)
enum class EBoarState : uint8
{
	Run,
	SlowMotion,
	Hit,
	Die
};

UENUM(BlueprintType)
enum class ELightState : uint8
{
	Stay,
	Day,
	Night
};

UENUM(BlueprintType)
enum class ETitleState : uint8
{
	On,
	Stay,
	Off
};

