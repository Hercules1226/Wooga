// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_SystemUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"
#include "SJ_UI_Next.h"

// Sets default values
ASJ_Actor_SystemUI::ASJ_Actor_SystemUI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Comp"));
	widgetComp->SetupAttachment(rootComp);

	nextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NextWidget"));
	nextWidget->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_SystemUI::BeginPlay()
{
	Super::BeginPlay();

	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	nextUI = Cast<USJ_UI_Next>(nextWidget->GetWidget());

	FVector playerLoc = player->GetActorLocation();
	FVector me = GetActorLocation();

	FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 200 + player->GetActorUpVector() * 50;

	SetActorLocation(p);

	FVector dir = player->GetActorLocation() - GetActorLocation();
	dir.Normalize();

	SetActorRotation(dir.Rotation());

	nextWidget->SetVisibility(false);

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
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= 3.0f)
	{
		nextWidget->SetVisibility(true);
		
		nextUI->OpenAnimation();

		currentTime = 0;

		SetState(EUIState::Next);
	}
}

void ASJ_Actor_SystemUI::Next()
{
	if (player->isClose == true)
	{
		nextUI->CloseAnimation();

		SetState(EUIState::Off);
	}
}

void ASJ_Actor_SystemUI::Off()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime >= 0.9f)
	{
		currentTime = 0;
		Destroy();
	}
}

