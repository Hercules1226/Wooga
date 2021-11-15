// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_TitleUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"

// Sets default values
ASJ_Actor_TitleUI::ASJ_Actor_TitleUI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	plane->SetupAttachment(rootComp);

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	widgetComp->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_TitleUI::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameMode->flowState == EFlowState::HowToGrabActorUI || gameMode->flowState == EFlowState::FireDiscoveryTitle)
	{
		FVector playerLoc = player->GetActorLocation();
		FVector me = GetActorLocation();

		FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 200 + player->GetActorUpVector() * 50;

		SetActorLocation(p);

		FVector dir = player->GetActorLocation() - GetActorLocation();
		dir.Normalize();

		SetActorRotation(dir.Rotation());
	}
	else if (gameMode->flowState == EFlowState::GoToCollectCourse || gameMode->flowState == EFlowState::CollectTitle)
	{
		FVector p1 = FVector(9850, 10150, 1270);

		SetActorLocation(p1);

		FVector dir = player->GetActorLocation() - GetActorLocation();
		dir.Normalize();

		SetActorRotation(dir.Rotation());
	}
	else if (gameMode->flowState == EFlowState::GoToFistAxCourse || gameMode->flowState == EFlowState::HandAxTitle)
	{
		FVector playerLoc = player->GetActorLocation();
		FVector me = GetActorLocation();

		FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 200 + player->GetActorUpVector() * 50;

		SetActorLocation(p);

		FVector dir = player->GetActorLocation() - GetActorLocation();
		dir.Normalize();

		SetActorRotation(dir.Rotation());
	}
	else if (gameMode->flowState == EFlowState::GoToFireUse || gameMode->flowState == EFlowState::FireUseTitle)
	{
		FVector p3 = FVector(5201, 7838, 1270);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, -50, 0);

		SetActorRotation(r3);
	}
}

// Called every frame
void ASJ_Actor_TitleUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

