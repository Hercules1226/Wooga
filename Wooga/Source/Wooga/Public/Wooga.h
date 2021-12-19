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
	HowToFireDiscovery,
	HowToFireUI,
	HowToFireUINext,
	Firing,
	CompleteFireDiscovery,
	InformWatch,
	SpawnCollectGuideLine,
	GoToCollectCourse,
	// ä��
	CollectTitle,
	HowToCollect,
	CollectAndEat,
	CompleteCollect,
	SpawnHandAxGuideLine,
	GoToFistAxCourse,
	// ���(�ָԵ���)
	HandAxTitle,
	HowToHunt,
	SeeMammoth,
	GrabHandAx,
	RunBoar,
	HitBoar,
	MakeHandAx,
	HowToMakeHandAx,
	IndirectnessHit,
	DirectlyHit,
	CompleteHandAx,
	// ���� Ȱ��
	CuttingPig,
	GoToFireUse,
	FireUseTitle,
	HowToFireUse,
	FiringTwo,
	CookMeat,
	EatMeat,
	CompleteFireUse,
	TestFunc,
	GoToSpear,
	// �������
	SpearTitle,
	HowTomakeSpear,
	MakeSpear,
	TakeRock,
	ConnectSpear,
	TieSpear,
	CompleteSpear,
	HuntFish,
	CatchFish,
	GoBackFireStraw,
	CanFreeMove,
	GoToCookFish,
	CookFish,
	EatFish,
	SpawnHutGuideLine,
	// ���� ����
	GoToHut,
	HutTitle,
	HowToMakeHut,
	MakeHut,
	CompleteHut,
	OutGame
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

UENUM(BlueprintType)
enum class ESaturateState : uint8
{
	OnSature,
	Stay,
	Next,
	OffSature
};

UENUM(BlueprintType)
enum class EUIState : uint8
{
	On,
	Stay,
	Next,
	Off
};
