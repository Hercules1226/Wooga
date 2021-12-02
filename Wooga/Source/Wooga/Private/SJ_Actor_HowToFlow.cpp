// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_HowToFlow.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PostProcessComponent.h>
#include "SJ_WoogaGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"
#include "Arrow1.h"
#include "Arrow2.h"
#include "Arrow3.h"
#include "Arrow4.h"
#include "Arrow5.h"
#include "Arrow6.h"
#include "Arrow7.h"
#include <Components/WidgetComponent.h>
#include "SJ_UI_Next.h"

// Sets default values
ASJ_Actor_HowToFlow::ASJ_Actor_HowToFlow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	howToPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HowToPlane"));
	howToPlane->SetupAttachment(rootComp);

	howToPost = CreateDefaultSubobject<UPostProcessComponent>(TEXT("HowToPost"));
	howToPost->SetupAttachment(rootComp);

	howToUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HowToUI"));
	howToUI->SetupAttachment(rootComp);

	nextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NextUI"));
	nextWidget->SetupAttachment(rootComp);

}

void ASJ_Actor_HowToFlow::BeginPlay()
{
	Super::BeginPlay();

	//nextUI->Deactivate();
	nextWidget->SetVisibility(false);

	UGameplayStatics::PlaySound2D(GetWorld(), onSound);

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	nextUI = Cast<USJ_UI_Next>(nextWidget->GetWidget());

	// 불의 발견(불피우기) 방법
	if (gameMode->flowState == EFlowState::FireDiscoveryTitle)
	{
		FVector p1 = FVector(10900, 11920, 1290);
		SetActorLocation(p1);

		FRotator r1 = FRotator(0, -30, 0);
		SetActorRotation(r1);

		playTime = 14;

		TArray<AActor*> bpArrow1;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArrow1::StaticClass(), bpArrow1);
		if (bpArrow1.Num() > 0)
		{
			for (int i = 0; i < bpArrow1.Num(); i++)
			{
				AArrow1* emptyArrow1 = nullptr;
				arrow1s.Add(emptyArrow1);
			}

			for (int i = 0; i < bpArrow1.Num(); i++)
			{
				auto arrow1 = Cast<AArrow1>(bpArrow1[i]);
				arrow1s[i] = arrow1;
				arrow1s[i]->arrowOn = true;
			}
		}

		flowIndex = 1;
	}
	// 채집하기 방법
	else if (gameMode->flowState == EFlowState::CollectTitle)
	{
		arrow2 = Cast<AArrow2>(UGameplayStatics::GetActorOfClass(GetWorld(), AArrow2::StaticClass()));
		arrow2->arrowOn = true;

		FVector p2 = FVector(9728, 10147, 1300);
		SetActorLocation(p2);

		FRotator r2 = FRotator(0, -45, 0);
		SetActorRotation(r2);

		flowIndex = 2;

		playTime = 3;
		arrow2->meshComp->SetHiddenInGame(false);
	}
	// 사냥하기 방법
	else if (gameMode->flowState == EFlowState::GrabHandAx)
	{
		FVector p3 = FVector(7710, 8977, 1300);

		SetActorLocation(p3);

		FRotator r3 = FRotator(0, -85, 0);

		SetActorRotation(r3);

		playTime = 8;
		flowIndex = 3;
	}
	// 주먹도끼 방법
	else if (gameMode->flowState == EFlowState::MakeHandAx)
	{
		FVector p4 = FVector(7694, 8915, 1309);

		SetActorLocation(p4);

		FRotator r4 = FRotator(0, -140, 0);

		SetActorRotation(r4);

		flowIndex = 4;

		arrow4 = Cast<AArrow4>(UGameplayStatics::GetActorOfClass(GetWorld(), AArrow4::StaticClass()));
		arrow4->arrowOn = true;

		playTime = 8;
	}
	else if (gameMode->flowState == EFlowState::FireUseTitle)
	{
		FVector p5 = FVector(5177, 7877, 1300);

		SetActorLocation(p5);

		FRotator r5 = FRotator(0, -140, 0);

		SetActorRotation(r5);

		flowIndex = 5;

		arrow5 = Cast<AArrow5>(UGameplayStatics::GetActorOfClass(GetWorld(), AArrow5::StaticClass()));
		arrow5->arrowOn = true;

		playTime = 9;
	}
	else if (gameMode->flowState == EFlowState::SpearTitle)
	{
		FVector p6 = FVector(4416, 6856, 1280);

		SetActorLocation(p6);

		FRotator r6 = FRotator(0, 0, 0);

		SetActorRotation(r6);

		TArray<AActor*> bpArrow6;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArrow6::StaticClass(), bpArrow6);
		if (bpArrow6.Num() > 0)
		{
			for (int i = 0; i < bpArrow6.Num(); i++)
			{
				AArrow6* emptyArrow6 = nullptr;
				arrow6s.Add(emptyArrow6);
			}

			for (int i = 0; i < bpArrow6.Num(); i++)
			{
				auto arrow6 = Cast<AArrow6>(bpArrow6[i]);
				arrow6s[i] = arrow6;
				arrow6s[i]->arrowOn = true;
			}
		}

		flowIndex = 6;

		playTime = 13;
	}
	else if (gameMode->flowState == EFlowState::HutTitle)
	{
		FVector p7 = FVector(4042, 7900, 1300);

		SetActorLocation(p7);

		FRotator r7 = FRotator(0, -145, 0);

		SetActorRotation(r7);

		TArray<AActor*> bpArrow7;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArrow7::StaticClass(), bpArrow7);
		if (bpArrow7.Num() > 0)
		{
			for (int i = 0; i < bpArrow7.Num(); i++)
			{
				AArrow7* emptyArrow7 = nullptr;
				arrow7s.Add(emptyArrow7);
			}

			for (int i = 0; i < bpArrow7.Num(); i++)
			{
				auto arrow7 = Cast<AArrow7>(bpArrow7[i]);
				arrow7s[i] = arrow7;
				arrow7s[i]->arrowOn = true;
			}
		}

		flowIndex = 7;

		playTime = 8;
	}



	SetState(ESaturateState::OnSature);

	/*
	startParam.bOverride_ColorSaturation = true;
	startParam.ColorSaturation = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
	howToPost->Settings = startParam;
	*/

	howToPlane->SetRenderCustomDepth(true);
}

void ASJ_Actor_HowToFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (saturateState)
	{
	case ESaturateState::OnSature:
		OnSature();
		break;
	case ESaturateState::Stay:
		Stay();
		break;
	case  ESaturateState::Next:
		Next();
		break;
	case ESaturateState::OffSature:
		OffSature();
		break;
	}
}

ESaturateState ASJ_Actor_HowToFlow::GetState()
{
	return ESaturateState();
}

void ASJ_Actor_HowToFlow::SetState(ESaturateState state)
{
	saturateState = state;
}

void ASJ_Actor_HowToFlow::OnSature()
{
	onTime += GetWorld()->DeltaTimeSeconds;

	startDissolveParam = FMath::Lerp(-1.0f, 1.0f, onTime);

	// howToPlane->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), startDissolveParam);

	// 포스트프로세스 흑백 조절
	/*
	float satValue = FMath::Lerp(1.0f, 0.4f, onTime);
	onParam.bOverride_ColorSaturation = true;
	onParam.ColorSaturation = FVector4(1.0f, 1.0f, 1.0f, satValue);
	howToPost->Settings = onParam;
	*/

	if (onTime >= 1.0f)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), howToSound);
		onTime = 0;
		SetState(ESaturateState::Stay);
	}
}

void ASJ_Actor_HowToFlow::Stay()
{

	currentTime += GetWorld()->GetDeltaSeconds();

	if (currentTime >= playTime)
	{
		nextWidget->SetVisibility(true);

		nextUI->OpenAnimation();

		currentTime = 0;
		SetState(ESaturateState::Next);
	}
}

void ASJ_Actor_HowToFlow::Next()
{
	if (player->isClose == true)
	{
		nextUI->CloseAnimation();
		SetState(ESaturateState::OffSature);
	}
}

void ASJ_Actor_HowToFlow::OffSature()
{
	offTime += GetWorld()->DeltaTimeSeconds;

	endDissolveParam = FMath::Lerp(1.0f, -1.0f, offTime);

	// howToPlane->SetScalarParameterValueOnMaterials(TEXT("Dissolve"), endDissolveParam);

	// 포스트 흑백 조절
	/*
	float offValue = FMath::Lerp(0.4f, 1.0f, offTime);
	offParam.bOverride_ColorSaturation = true;
	offParam.ColorSaturation = FVector4(1.0f, 1.0f, 1.0f, offValue);
	howToPost->Settings = offParam;
	*/

	if (offTime >= 1.0f)
	{
		offTime = 0;

		if (flowIndex == 1)
		{
			// 불의 발견 설명 액터 끄기
			TArray<AActor*> bpArrow1;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArrow1::StaticClass(), bpArrow1);
			if (bpArrow1.Num() > 0)
			{
				for (int i = 0; i < bpArrow1.Num(); i++)
				{
					AArrow1* emptyArrow1 = nullptr;
					arrow1s.Add(emptyArrow1);
				}

				for (int i = 0; i < bpArrow1.Num(); i++)
				{
					auto arrow1 = Cast<AArrow1>(bpArrow1[i]);
					arrow1s[i] = arrow1;
					arrow1s[i]->arrowOn = false;
				}
			}


		}

		if (flowIndex == 2)
		{
			arrow2->arrowOn = false;
		}

		if (flowIndex == 3)
		{

		}

		if (flowIndex == 4)
		{
			arrow4->arrowOn = false;
		}

		if (flowIndex == 5)
		{
			arrow5->arrowOn = false;
		}

		if (flowIndex == 6)
		{
			TArray<AActor*> bpArrow6;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArrow6::StaticClass(), bpArrow6);
			if (bpArrow6.Num() > 0)
			{
				for (int i = 0; i < bpArrow6.Num(); i++)
				{
					AArrow6* emptyArrow6 = nullptr;
					arrow6s.Add(emptyArrow6);
				}

				for (int i = 0; i < bpArrow6.Num(); i++)
				{
					auto arrow6 = Cast<AArrow6>(bpArrow6[i]);
					arrow6s[i] = arrow6;
					arrow6s[i]->arrowOn = false;
				}
			}
		}

		if (flowIndex == 7)
		{
			TArray<AActor*> bpArrow7;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArrow7::StaticClass(), bpArrow7);
			if (bpArrow7.Num() > 0)
			{
				for (int i = 0; i < bpArrow7.Num(); i++)
				{
					AArrow7* emptyArrow7 = nullptr;
					arrow7s.Add(emptyArrow7);
				}

				for (int i = 0; i < bpArrow7.Num(); i++)
				{
					auto arrow7 = Cast<AArrow7>(bpArrow7[i]);
					arrow7s[i] = arrow7;
					arrow7s[i]->arrowOn = false;
				}
			}
		}

		SetState(ESaturateState::OnSature);
		Destroy();
	}
}

