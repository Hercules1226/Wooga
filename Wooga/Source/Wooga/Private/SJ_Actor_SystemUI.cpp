// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_SystemUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"
#include "SJ_UI_Next.h"
#include "SJ_UI_SystemUI.h"
#include <Kismet/GameplayStatics.h>

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

   // 위치
	if (gameModeBase->flowState == EFlowState::InGame)
	{
		FVector p1 = FVector(10800, 12106, 1322);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0, -17, 0);

		SetActorRotation(r1);
	}

	if (gameModeBase->flowState == EFlowState::ManipulateUI)
	{
		FVector p2 = FVector(10800, 12106, 1322);

		SetActorLocation(p2);

		FRotator r2 = FRotator(0, -17, 0);

		SetActorRotation(r2);
	}

	if (gameModeBase->flowState == EFlowState::CompleteFireDiscovery)
	{
		FVector p3 = FVector(10728, 11906, 1320);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, -16, 0);

		SetActorRotation(r3);
	}

	if (gameModeBase->flowState == EFlowState::GoBackFireStraw)
	{
		FVector p4  = FVector(4328, 7343, 1330);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, -175, 5);

		SetActorRotation(r4);
	}

	// UI 오픈 사운드
	UGameplayStatics::PlaySound2D(GetWorld(), openSound);

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

	startDissolveParam = FMath::Lerp(0.0f, 1.0f, onTime);

	plane->SetScalarParameterValueOnMaterials(TEXT("Opacity"), startDissolveParam);

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
		UGameplayStatics::PlaySound2D(GetWorld(), closeSound);
		nextController->SetHiddenInGame(true);
		nextBlink->SetHiddenInGame(true);
		SetState(EUIState::Off);
	}
}

void ASJ_Actor_SystemUI::Off()
{
	offTime += GetWorld()->DeltaTimeSeconds;

	endDissolveParam = FMath::Lerp(1.0f, 0.0f, offTime);

	plane->SetScalarParameterValueOnMaterials(TEXT("Opacity"), endDissolveParam);

	if (offTime >= 1.0f)
	{
		offTime = 0;
		Destroy();
	}
}

