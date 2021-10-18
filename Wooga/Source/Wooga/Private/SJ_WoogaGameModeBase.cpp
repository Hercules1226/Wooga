// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_WoogaGameModeBase.h"
#include "SJ_UIPannel.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireRock.h"
#include "FireStraw.h"
#include "SJ_Hologram.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetFlowState(EFlowState::FireDiscovery);

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	player->uiPannel = GetWorld()->SpawnActor<ASJ_UIPannel>(howToGrab, Param);
}

void ASJ_WoogaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
#pragma region FlowStateMachine
	switch (flowState)
	{
	case EFlowState::FireDiscovery:
		break;
	case EFlowState::Collection:
		break;
	case EFlowState::FistAx:
		break;
	case EFlowState::FireUse:
		break;
	case EFlowState::Smelts:
		break;
	case EFlowState::DugoutHut:
		break;
	}
#pragma endregion

#pragma region DiscoveryStateMachine
	switch (discoveryState)
	{
	case EFireDiscoveryState::GrabActorUI:
		GrabActorUI();
		break;
	case EFireDiscoveryState::Firing:
		break;
	case EFireDiscoveryState::CompleteCourse:
		break;
	case EFireDiscoveryState::InformWatch:
		break;
	case EFireDiscoveryState::GoToNextStep:
		break;
	}

#pragma endregion

}

void ASJ_WoogaGameModeBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// PlayerInputComponent->BindAction("TurnOffUI", IE_Pressed, this, &ASJ_WoogaGameModeBase::TurnOff);
}

#pragma region FlowStateFunction
// ĸ��ȭ
void ASJ_WoogaGameModeBase::SetFlowState(EFlowState state)
{
	flowState = state;
}

EFlowState ASJ_WoogaGameModeBase::GetFlowState()
{
	return EFlowState();
}

void ASJ_WoogaGameModeBase::FireDiscovery()
{
	SetDiscoveryState(EFireDiscoveryState::GrabActorUI);
	
}

void ASJ_WoogaGameModeBase::Collection()
{

}

void ASJ_WoogaGameModeBase::FistAx()
{

}

void ASJ_WoogaGameModeBase::FireUse()
{

}

void ASJ_WoogaGameModeBase::Smelts()
{

}

void ASJ_WoogaGameModeBase::DogoutHut()
{

}

#pragma endregion

#pragma region DiscoveryStateFunction
void ASJ_WoogaGameModeBase::SetDiscoveryState(EFireDiscoveryState state)
{
	discoveryState = state;
}
EFireDiscoveryState ASJ_WoogaGameModeBase::GetDiscoveryState()
{
	return EFireDiscoveryState();
}

void ASJ_WoogaGameModeBase::GrabActorUI()
{
	if (player->isClose == true)
	{
		SetDiscoveryState(EFireDiscoveryState::Firing);
		// UI �� ���� ��ó �ƿ� ������ ������
	}
}
void ASJ_WoogaGameModeBase::Firing()
{
	// ���� �Ѹ� Ȧ�α׷��� �����Ǵ� ���
	AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (fireStraw->isClear == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire"));
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<ASJ_Hologram>(fireDisCoveryHologram, Param);
		SetDiscoveryState(EFireDiscoveryState::CompleteCourse);
	}
}
void ASJ_WoogaGameModeBase::CompleteFireCourse()
{
	// Ȧ�α׷��� ������ �ð�� ���� ���
	// �ð� ��ƽ ���
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// �ð� ���� UI ���� �� A ��ư���� ���� ���
	// UI�� ���� �̵� ����� �˷��ִ� UI ���� �� �̵� ���̵���� ����
}
void ASJ_WoogaGameModeBase::GoToCollectState()
{

}
#pragma endregion

void ASJ_WoogaGameModeBase::TurnOff()
{
	useUI->SetActorHiddenInGame(true);
}
