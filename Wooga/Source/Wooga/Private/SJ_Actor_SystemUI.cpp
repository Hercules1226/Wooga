// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_SystemUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"
#include "SJ_UI_Next.h"
#include "SJ_UI_SystemUI.h"

// Sets default values
ASJ_Actor_SystemUI::ASJ_Actor_SystemUI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	nextController = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NextController"));
	nextController->SetupAttachment(rootComp);

	nextBlink = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NextBlink"));
	nextBlink->SetupAttachment(rootComp);

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	widgetComp->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_SystemUI::BeginPlay()
{
	Super::BeginPlay();

	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	nextController->SetHiddenInGame(true);
	nextBlink->SetHiddenInGame(true);

	// systemUI = Cast<USJ_UI_SystemUI>(widgetComp->GetWidget());

   /*
   FVector playerLoc = player->GetActorLocation();
   FVector me = GetActorLocation();

   FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 200 + player->GetActorUpVector() * 50;

   SetActorLocation(p);

   FVector dir = player->GetActorLocation() - GetActorLocation();
   dir.Normalize();

   SetActorRotation(dir.Rotation());
   */

   // ��ġ
	if (gameModeBase->flowState == EFlowState::InGame)
	{
		FVector p = FVector(10809, 12123, 1363);

		SetActorLocation(p);

		FRotator r = FRotator(-2, -12, 0);

		SetActorRotation(r);
	}

	if (gameModeBase->flowState == EFlowState::ManipulateUI)
	{
		FVector p = FVector(10809, 12123, 1363);

		SetActorLocation(p);

		FRotator r = FRotator(-2, -12, 0);

		SetActorRotation(r);
	}

	if (gameModeBase->flowState == EFlowState::CompleteFireDiscovery)
	{
		FVector p = FVector(10780, 11899, 1363);

		SetActorLocation(p);

		FRotator r = FRotator(0, 82, 0);

		SetActorRotation(r);
	}

	SetState(EUIState::On);
}

// Called every frame
void ASJ_Actor_SystemUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (uiState)
	{
	case EUIState::On:
		On();
		break;
	case EUIState::Stay:
		Stay();
		break;
	case EUIState::Next:
		Next();
		break;
	case EUIState::Off:
		Off();
		break;
	}
}

EUIState ASJ_Actor_SystemUI::GetState()
{
	return EUIState();
}

void ASJ_Actor_SystemUI::SetState(EUIState state)
{
	uiState = state;
}

void ASJ_Actor_SystemUI::On()
{
	onTime += GetWorld()->DeltaTimeSeconds;

	startDissolveParam = FMath::Lerp(-1.0f, 1.0f, onTime * 2);

	plane->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), startDissolveParam);

	if (onTime >= 1.0f)
	{
		onTime = 0;

		SetState(EUIState::Stay);
	}
}

void ASJ_Actor_SystemUI::Stay()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= 3.0f)
	{
		nextController->SetHiddenInGame(false);
		nextBlink->SetHiddenInGame(false);

		currentTime = 0;
		SetState(EUIState::Next);
	}
}

void ASJ_Actor_SystemUI::Next()
{
	if (player->isClose == true)
	{
		nextController->SetHiddenInGame(true);
		nextBlink->SetHiddenInGame(true);
		SetState(EUIState::Off);
	}
}

void ASJ_Actor_SystemUI::Off()
{
	offTime += GetWorld()->DeltaTimeSeconds;

	endDissolveParam = FMath::Lerp(1.0f, -1.0f, offTime);

	plane->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), endDissolveParam);

	if (offTime >= 1.0f)
	{
		offTime = 0;
		Destroy();
	}
}

