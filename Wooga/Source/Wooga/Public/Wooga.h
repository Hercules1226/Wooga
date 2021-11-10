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
	HowToFireUI,
	HowToFireUINext,
	Firing,
	CompleteFireDiscovery,
	InformWatch,
	GoToCollectCourse,
	// 채집
	CollectTitle,
	HowToCollectActorUI,
	CollectAndEat,
	CompleteCollect,
	GoToFistAxCourse,
	// 사냥(주먹도끼)
	HandAxTitle,
	SeeMammoth,
	GrabHandAx,
	RunBoar,
	HitBoar,
	MakeHandAx,
	IndirectnessHit,
	DirectlyHit,
	CompleteHandAx
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