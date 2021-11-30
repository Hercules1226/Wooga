// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EFlowState : uint8
{
	InGame,
	ManipulateUI,
	HowToGrabActorUI,
	// 불의  발견
	FireDiscoveryTitle,
	HowToFireDiscovery,
	HowToFireUI,
	HowToFireUINext,
	Firing,
	CompleteFireDiscovery,
	InformWatch,
	SpawnCollectGuideLine,
	GoToCollectCourse,
	// 채집
	CollectTitle,
	HowToCollect,
	CollectAndEat,
	CompleteCollect,
	SpawnHandAxGuideLine,
	GoToFistAxCourse,
	// 사냥(주먹도끼)
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
	// 불의 활용
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
	// 슴베찌르개
	SpearTitle,
	HowTomakeSpear,
	MakeSpear,
	TakeRock,
	ConnectSpear,
	TieSpear,
	CompleteSpear,
	HuntFish,
	CatchFish,
	GoToCookFish,
	CookFish,
	EatFish,
	SpawnHutGuideLine,
	// 움집 제작
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
	OffSature
};

