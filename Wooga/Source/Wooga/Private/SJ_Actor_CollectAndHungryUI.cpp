// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_CollectAndHungryUI.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASJ_Actor_CollectAndHungryUI::ASJ_Actor_CollectAndHungryUI()
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
void ASJ_Actor_CollectAndHungryUI::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	// ���� ��ġ ����

	// �÷��̾� ��ġ
	FVector playerLoc = player->GetActorLocation();
	// UI ��ġ
	FVector me = GetActorLocation();

	FVector p = player->GetActorLocation() + player->GetActorForwardVector() * 200 + player->GetActorUpVector() * 50;

	SetActorLocation(p);

	// Target - me -> UI �÷��̾ ���� �� �� �ֵ���.
	FVector dir = player->GetActorLocation() - GetActorLocation();
	dir.Normalize();

	SetActorRotation(dir.Rotation());
}

// Called every frame
void ASJ_Actor_CollectAndHungryUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

