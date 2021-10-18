// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_WoogaGameModeBase.h"
#include "SJ_UIPannel.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetFlowState(EFlowState::FireDiscovery);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	float playerX = player->GetActorLocation().X ;
	float playerY = player->GetActorLocation().Y;
	float playerZ = player->GetActorLocation().Z;

	p = FVector(playerX + 50, playerY, playerZ);

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ���� �� HMD�� ���� UI ���� �� A ��ư���� UI ���� ���
	GetWorld()->SpawnActor<ASJ_UIPannel>(howToGrab, Param);

}

void ASJ_WoogaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

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
}

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
	
	// UI �� ���� ��ó �ƿ� ������ ������
	// ���� �Ѹ� Ȧ�α׷��� �����Ǵ� ���
	// Ȧ�α׷��� ������ �ð�� ���� ���
	// �ð� ��ƽ ���
	// �ð� ���� UI ���� �� A ��ư���� ���� ���
	// UI�� ���� �̵� ����� �˷��ִ� UI ���� �� �̵� ���̵���� ����
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