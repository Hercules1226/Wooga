// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_WoogaGameModeBase.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireRock.h"
#include "FireStraw.h"
#include "SJ_Hologram.h"
#include "GrabActorComponent.h"
#include "SJ_GuidLine.h"
#include "SJ_HowToGrabUIActor.h"
#include "SJ_HowToFireUIActor.h"
#include <Components/WidgetComponent.h>
#include "FirePosition.h"
#include "SJ_HowToFireNextUIActor.h"
#include "SJ_Actor_HowToManipulate.h"
#include "SJ_Actor_TitleUI.h"
#include "FireRock2.h"
#include "SJ_Actor_BreatheFireUI.h"
#include "SJ_Actor_WatchInformUI.h"
#include "Apple.h"
#include "SJ_Actor_EatAppleUI.h"
#include "SJ_Actor_CollectAndHungryUI.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/LightComponent.h"
#include "SJ_Actor_GoToGuideLine.h"
#include "SJ_Actor_MammothSpawnDestroy.h"
#include "SJ_Character_Boar.h"
#include "SJ_Actor_GrabHandAxUI.h"
#include "SJ_Actor_HitBoarUI.h"
#include "SJ_Actor_MakeHandAxUI.h"
#include "FistAxe.h"
#include "SJ_Actor_IndirectHitUI.h"
#include "SJ_Actor_DirectHitUI.h"
#include "SJ_Actor_Hologram.h"
#include "SJ_Actor_CuttingPigUI.h"
#include "Engine/DirectionalLight.h"
#include "SJ_Actor_PickUpMeatUI.h"
#include "SJ_Actor_FireTwoUI.h"
#include "SlicePig.h"
#include "SliceMeat.h"
#include "Cutting.h"
#include "Cutting2.h"
#include "SJ_Actor_MakeRange.h"
#include "SJ_Actor_LevelLight.h"
#include "SJ_Actor_Title.h"
#include "Tomahowk.h"
#include "SJ_Actor_CookUI.h"
#include "SJ_Actor_EatMeatUI.h"
#include "SJ_Actor_GrabTomahowkUI.h"
#include "SJ_Actor_BreakStoneUI.h"
#include "SumjjiRock.h"
#include "SJ_Actor_ConnectSpearUI.h"
#include "Cable.h"
#include "SJ_Actor_TieSpearUI.h"
#include "String.h"
#include "SJ_Actor_HuntFishUI.h"
#include "SJ_Actor_CatchFish.h"
#include "SJ_Actor_CatchFishUI.h"
#include "SJ_Actor_GoFryFishUI.h"
#include "SJ_Actor_CookFishUI.h"
#include "SJ_Actor_EatFishUI.h"
#include "SJ_Actor_GoToHutUI.h"
#include "SJ_Actor_MakeHutUI.h"
#include "LastHouse.h"
#include "SJ_Actor_HowToFlow.h"
#include "SJ_Actor_MakeSpearUI.h"
#include "Stick.h"
#include "SJ_Actor_SystemUI.h"
#include "SJ_Actor_Bird.h"
#include "SJ_Actor_RunDeer.h"
#include "MoveSpline.h"
#include "SJ_Actor_Mammoth.h"
#include "SJ_ChangeFreeMove.h"
#include "MoveActorComponent.h"

ASJ_WoogaGameModeBase::ASJ_WoogaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASJ_WoogaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	 SetState(EFlowState::InGame);

	// ?? ???? ???? ???? ???????? ????
	// SetState(EFlowState::SpawnHutGuideLine);
	// SetState(EFlowState::SpawnHandAxGuideLine);

	// ???????? ????????
	//SetState(EFlowState::CompleteCollect);

	// ???? ????????
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ???????? ??????
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	// ???? ????
	slicePig = Cast<ASlicePig>(UGameplayStatics::GetActorOfClass(GetWorld(), ASlicePig::StaticClass()));
	slicePig->SetActorHiddenInGame(true);

	// ???? ?????? 1
	cutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));
	cutting->SetActorHiddenInGame(true);

	// ???? ??????2
	// cuttingTwo = Cast<ACutting2>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting2::StaticClass()));
	// cuttingTwo->SetActorHiddenInGame(true);

	// ???? ????
	// sliceMeat = Cast<ASliceMeat>(UGameplayStatics::GetActorOfClass(GetWorld(), ASliceMeat::StaticClass()));
	// sliceMeat->SetActorHiddenInGame(true);

	// ????????
	tomahowk = Cast<ATomahowk>(UGameplayStatics::GetActorOfClass(GetWorld(), ATomahowk::StaticClass()));
	tomahowk->SetActorHiddenInGame(true);

	// ????
	lastHouse = Cast<ALastHouse>(UGameplayStatics::GetActorOfClass(GetWorld(), ALastHouse::StaticClass()));
	lastHouse->SetActorHiddenInGame(true);

	// ??????
	levelLight = Cast<ASJ_Actor_LevelLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_LevelLight::StaticClass()));

	moveSpine = Cast<AMoveSpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMoveSpline::StaticClass()));

	// ?????? ???????? ?????? ????????.
	// moveSpine->canMove = true;
	
	moveSpine->canMove = false;

	freeMove = Cast<ASJ_ChangeFreeMove>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_ChangeFreeMove::StaticClass()));
}

#pragma region FlowStateFunction
void ASJ_WoogaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (flowState)
	{
	case EFlowState::InGame:
		InGame();
		break;
	case  EFlowState::ManipulateUI:
		ManipulateUI();
		break;
	case EFlowState::HowToGrabActorUI:
		GrabActorUI();
		break;
	case EFlowState::FireDiscoveryTitle:
		FireDiscoveryTitle();
		break;
	case EFlowState::HowToFireDiscovery:
		HowToFIreDiscovery();
		break;
	case EFlowState::HowToFireUI:
		HowToFireUI();
		break;
	case EFlowState::HowToFireUINext:
		HowToFireUINext();
		break;
	case EFlowState::Firing:
		Firing();
		break;
	case EFlowState::CompleteFireDiscovery:
		CompleteFireCourse();
		break;
	case EFlowState::InformWatch:
		InformWatch();
		break;
	case  EFlowState::SpawnCollectGuideLine:
		SpawnCollectGuideLine();
		break;
	case EFlowState::GoToCollectCourse:
		GoToCollectState();
		break;
	case EFlowState::CollectTitle:
		CollectTitle();
		break;
	case EFlowState::HowToCollect:
		HowToCollect();
		break;
	case EFlowState::CollectAndEat:
		CollectAndEat();
		break;
	case EFlowState::CompleteCollect:
		CompleteCollect();
		break;
	case EFlowState::SpawnHandAxGuideLine:
		SpawnHandAxGuideLine();
		break;
	case EFlowState::GoToFistAxCourse:
		GoToFistAxCourse();
		break;
	case  EFlowState::HandAxTitle:
		HandAxTitle();
		break;
	case EFlowState::HowToHunt:
		HowToHunt();
		break;
	case EFlowState::GrabHandAx:
		GrabHandAx();
		break;
	case  EFlowState::RunBoar:
		RunBoar();
		break;
	case EFlowState::HitBoar:
		HitBoar();
		break;
	case EFlowState::MakeHandAx:
		MakeHandAx();
		break;
	case EFlowState::HowToMakeHandAx:
		HowToMakeHandAx();
		break;
	case EFlowState::IndirectnessHit:
		IndirectHit();
		break;
	case EFlowState::DirectlyHit:
		DirectHit();
		break;
	case  EFlowState::CompleteHandAx:
		CompleteHandAx();
		break;
	case EFlowState::CuttingPig:
		CuttingPig();
		break;
	case EFlowState::GoToFireUse:
		GoToFireUse();
		break;
	case EFlowState::FireUseTitle:
		FireUseTitle();
		break;
	case EFlowState::HowToFireUse:
		HowToFireUse();
		break;
	case EFlowState::FiringTwo:
		FiringTwo();
		break;
	case EFlowState::CookMeat:
		CookMeat();
		break;
	case  EFlowState::EatMeat:
		EatMeat();
		break;
	case EFlowState::CompleteFireUse:
		CompleteFireUse();
		break;
	case EFlowState::GoToSpear:
		GoToSpear();
		break;
	case EFlowState::SpearTitle:
		SpearTitle();
		break;
	case EFlowState::MakeSpear:
		MakeSpear();
		break;
	case EFlowState::HowTomakeSpear:
		HowToMakeSpear();
		break;
	case EFlowState::TakeRock:
		TakeRock();
		break;
	case  EFlowState::ConnectSpear:
		ConnectSpear();
		break;
	case EFlowState::TieSpear:
		TieSpear();
		break;
	case EFlowState::CompleteSpear:
		CompleteSpear();
		break;
	case EFlowState::HuntFish:
		HuntFish();
		break;
	case EFlowState::CatchFish:
		CatchFish();
		break;
	case EFlowState::GoBackFireStraw:
		GoBackFireStraw();
		break;
	case EFlowState::CanFreeMove:
		CanFreeMove();
		break;
	case EFlowState::GoToCookFish:
		GoToCookFish();
		break;
	case EFlowState::CookFish:
		CookFish();
		break;
	case EFlowState::EatFish:
		EatFish();
		break;
	case  EFlowState::SpawnHutGuideLine:
		SpawnHutGuideLine();
		break;
	case  EFlowState::GoToHut:
		GoToHut();
		break;
	case EFlowState::HutTitle:
		HutTitle();
		break;
	case EFlowState::HowToMakeHut:
		HowToMakeHut();
		break;
	case EFlowState::MakeHut:
		MakeHut();
		break;
	case EFlowState::CompleteHut:
		CompleteHut();
		break;
	case EFlowState::OutGame:
		OutGame();
		break;
	}

	// UI ????
	if (bIsUIClose == true)
	{
		isDelay = true;
	}

	if (isDelay == true)
	{
		uiChange += DeltaSeconds;

		if (uiChange >= 0.1f)
		{
			bIsUIClose = false;
		}

		if (uiChange >= 1.0f)
		{
			uiChange = 0;
			isDelay = false;
		}
	}
}

// ??????
void ASJ_WoogaGameModeBase::SetState(EFlowState state)
{
	flowState = state;
}

EFlowState ASJ_WoogaGameModeBase::GetState()
{
	return EFlowState();
}

void ASJ_WoogaGameModeBase::InGame()
{
	// ???? ?? ?????? ???????? ???? ????
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 5.0f)
	{
		// ???????? UI ????
		systemUI = GetWorld()->SpawnActor<ASJ_Actor_SystemUI>(bpMoveSystemUI, Param);

		nextDelayTime = 0;

		SetState(EFlowState::ManipulateUI);
	}
}

void ASJ_WoogaGameModeBase::ManipulateUI()
{
	systemUIDelayTime += GetWorld()->DeltaTimeSeconds;

	if (systemUIDelayTime >= 4.0f)
	{
		// ???? UI?? ????,
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
	}

	// ?????? ??????
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		// 3?? ???? ?????? ???? ??????.
		// ???????? ???? ?????? ????????.
		if (nextDelayTime >= 1.5f)
		{
			// ?????? ???? ???? ???????? UI ???? ????
			systemUI = GetWorld()->SpawnActor<ASJ_Actor_SystemUI>(bpGrabSystemUI, Param);

			// ?????? ???? ??????
			bIsDelay = false;
			nextDelayTime = 0;
			systemUIDelayTime = 0;

			// ?????? UI ????
			// systemUI->Destroy();

			SetState(EFlowState::HowToGrabActorUI);
		}
	}
}

void ASJ_WoogaGameModeBase::GrabActorUI()
{
	UE_LOG(LogTemp,Warning,TEXT("GrabUI"));
	systemUIDelayTime += GetWorld()->DeltaTimeSeconds;
	if (systemUIDelayTime >= 4.0f)
	{
		// ???? ?????? ???????? UI ?? ?????? ???? ?????? ????????.
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
	}

	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ?????? ???? ??????
			bIsDelay = false;
			nextDelayTime = 0;
			systemUIDelayTime = 0;

			// ?????? UI ????
			// systemUI->Destroy();

			// ???? ???? ????
			// titleUI = GetWorld()->SpawnActor<ASJ_Actor_TitleUI>(bpFDTitle, Param);
			title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpFDTitle, Param);

			SetState(EFlowState::FireDiscoveryTitle);
		}
	}
}
#pragma endregion

#pragma region DiscoveryStateFunction
void ASJ_WoogaGameModeBase::FireDiscoveryTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpFDHowToFlow, Param);

		// ?????????? ??????
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireDiscovery);
	}
}

void ASJ_WoogaGameModeBase::HowToFIreDiscovery()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 15.0f)
	{
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// ?????? ????
				fireRockOne = Cast<AFireRock>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock::StaticClass()));
				fireRockTwo = Cast<AFireRock2>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock2::StaticClass()));

				// ?????? ????????
				fireRockOne->outLine->SetVisibility(true);
				fireRockTwo->outLine->SetVisibility(true);

				// ???? UI ????
				howToFire = GetWorld()->SpawnActor<ASJ_HowToFireUIActor>(howToFireUIActor, Param);

				howToNarTime = 0;
				nextDelayTime = 0;
				bIsDelay = false;

				moveSpine->canMove = true;

				SetState(EFlowState::HowToFireUI);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::HowToFireUI()
{
	// ?????????? ???? ????
	firePosition = Cast<AFirePosition>(UGameplayStatics::GetActorOfClass(GetWorld(), AFirePosition::StaticClass()));

	fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (firePosition->bisFire == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		// UI ??????
		bIsUIClose = true;

		if (nextDelayTime >= 1.0f)
		{
			// ?????? ???????? ??????
			fireRockOne->outLine->SetHiddenInGame(true);
			fireRockTwo->outLine->SetHiddenInGame(true);

			// ?????????? ???? ????????
			firePosition->outLine->SetVisibility(true);
			fireStraw->outLine->SetVisibility(true);

			//  ???? ???????? ?????? UI
			howToFireNext = GetWorld()->SpawnActor<ASJ_HowToFireNextUIActor>(howToFireNextUIActor, Param);

			// ?????? UI ????
			howToFire->Destroy();

			nextDelayTime = 0;

			SetState(EFlowState::HowToFireUINext);
		}
	}
}

void ASJ_WoogaGameModeBase::HowToFireUINext()
{
	// firePosition = Cast<AFirePosition>(UGameplayStatics::GetActorOfClass(GetWorld(), AFirePosition::StaticClass()));

	// fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	if (fireStraw->bisReadyFire == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			breatheFireUI = GetWorld()->SpawnActor<ASJ_Actor_BreatheFireUI>(bpBreatheFireUI, Param);

			// ?????? UI ????
			howToFireNext->Destroy();

			// ?????? ???? ??????
			nextDelayTime = 0;
			SetState(EFlowState::Firing);
		}
	}
}

void ASJ_WoogaGameModeBase::Firing()
{
	// AFireStraw* fireStraw = Cast<AFireStraw>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireStraw::StaticClass()));

	// ???? ???? ?????????? ???????? ?????? ???? ???? ?????? ????????.
	if (fireStraw->isClear == true)
	{
		// ?????????? ???? ????????
		// firePosition->outLine->SetHiddenInGame(true);
		fireStraw->outLine->SetHiddenInGame(true);

		// ?????? UI ????
		breatheFireUI->Destroy();

		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 3.0f)
		{
			// ???????? ????
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpFDHologram, Param);

			// ?????? ???? ??????
			nextDelayTime = 0;
			// bIsDelay = true;

			// ???? ???? ????
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			// ???????? ???? ??????
			player->playerWatch->SetHiddenInGame(false);

			SetState(EFlowState::CompleteFireDiscovery);
		}
	}
}

void ASJ_WoogaGameModeBase::CompleteFireCourse()
{
	// ?????????? ?????? ?????? ???????? ????
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 16)
	{
		// ?????? ???? ??????
		nextDelayTime = 0;

		systemUI = GetWorld()->SpawnActor<ASJ_Actor_SystemUI>(bpKnowledgeInformUI, Param);

		SetState(EFlowState::InformWatch);
	}
}
void ASJ_WoogaGameModeBase::InformWatch()
{
	// ???? ???? UI ???? ?? A ???????? ???? ????
	// UI?? ???? ???? ?????? ???????? UI ???? ?? ???? ?????????? ????
	systemUIDelayTime += GetWorld()->DeltaTimeSeconds;

	if (systemUIDelayTime >= 4.0f)
	{
		// ???? ?????? ???????? UI ?? ?????? ???? ?????? ????????.
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
	}

	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{			
			// ?????? ???? ??????
			bIsDelay = false;
			nextDelayTime = 0;
			systemUIDelayTime = 0;

			moveSpine->canMove = true;

			SetState(EFlowState::SpawnCollectGuideLine);
		}
	}
}

void ASJ_WoogaGameModeBase::SpawnCollectGuideLine()
{
	// ?????????? ????
	goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpCollectGuideLine, Param);
	levelLight->isDay = true;

	SetState(EFlowState::GoToCollectCourse);
}

void ASJ_WoogaGameModeBase::GoToCollectState()
{
	if (goToGuideLine->isTrigger == true)
	{
		// ?????? ???? ?????? ???? ???? ????
		// fireStraw->Destroy();

		// ???????? ???? UI ????
		title = GetWorld()->SpawnActor<class ASJ_Actor_Title>(bpCollectTitle, Param);

		moveSpine->canMove = false;

		// ???? ?????? ????????
		SetState(EFlowState::CollectTitle);
	}
}
#pragma endregion

#pragma region CollectStateFunction
void ASJ_WoogaGameModeBase::CollectTitle()
{
	// ???? ?????? ????
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ?????????? ??????
		goToGuideLine->Destroy();

		// ?????????? ??????
		nextDelayTime = 0;

		// ???????? ???? UI
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpCollectHowToFlow, Param);

		// ???? ???????? ???????? ??????
		apple = Cast<AApple>(UGameplayStatics::GetActorOfClass(GetWorld(), AApple::StaticClass()));

		apple->outLine->SetVisibility(true);

		SetState(EFlowState::HowToCollect);
	}
}

void ASJ_WoogaGameModeBase::HowToCollect()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 4.0f)
	{
		// UI ?? ????
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// ???? ?????? ???? UI
				eatAppleUI = GetWorld()->SpawnActor<ASJ_Actor_EatAppleUI>(bpEatAppleUI, Param);

				// ?????????? ??????
				bIsDelay = false;
				howToNarTime = 0;
				nextDelayTime = 0;

				moveSpine->canMove = true;

				SetState(EFlowState::CollectAndEat);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::CollectAndEat()
{
	// ???????? ?????? ???????? ???????? ???? ?????? ????????
	if (apple->bisEatComplete == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		bIsUIClose = true;

		if (nextDelayTime >= 1.0f)
		{
			// ???? ???????? ????
			hologram = GetWorld()->SpawnActor< ASJ_Hologram>(bpCollectHologram, Param);

			// ?????? UI ????
			eatAppleUI->Destroy();
			// ?????? ???? ??????
			nextDelayTime = 0;
			SetState(EFlowState::CompleteCollect);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteCollect()
{
	// ???????? ?????? ?????? ???????? ?????? ???????? 
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 10)
	{
		nextDelayTime = 0;

		// moveSpine->canMove = true;
		SetState(EFlowState::SpawnHandAxGuideLine);
	}
}

void ASJ_WoogaGameModeBase::SpawnHandAxGuideLine()
{
	// ?????????? ????
	goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHandAxGuideLine, Param);

	SetState(EFlowState::GoToFistAxCourse);
}

void ASJ_WoogaGameModeBase::GoToFistAxCourse()
{
	if (goToGuideLine->isTrigger == true)
	{
		// ????????(????????) ???? ????
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpHandAxTitle, Param);

		moveSpine->canMove = false;

		SetState(EFlowState::HandAxTitle);
	}
}

#pragma endregion

#pragma region HandAxFunction
void ASJ_WoogaGameModeBase::HandAxTitle()
{
	// ???? ?????? ????
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ?????????? ??????
		goToGuideLine->Destroy();

		// ???????? ?? ???? UI ????
		handAxUI = GetWorld()->SpawnActor<ASJ_Actor_GrabHandAxUI>(bpHandAxUI, Param);

		// ???????? ?? ????????
		fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
		fistAxe->handHologramL->SetHiddenInGame(false);
		fistAxe->bisStartBreak = false;

		// ?? ????????
		TArray<AActor*> bpBird;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASJ_Actor_Bird::StaticClass(), bpBird);

		for (int i = 0; i < bpBird.Num(); i++)
		{
			ASJ_Actor_Bird* emptyBird = nullptr;
			birds.Add(emptyBird);
		}
		for (int i = 0; i < bpBird.Num(); i++)
		{
			auto bird = Cast<ASJ_Actor_Bird>(bpBird[i]);
			birds[i] = bird;
			birds[i]->Fly();
		}

		UGameplayStatics::PlaySound2D(GetWorld(), birdSound);

		// ?????????? ??????
		nextDelayTime = 0;

		moveSpine->canMove = true;

		SetState(EFlowState::GrabHandAx);
	}
}

void ASJ_WoogaGameModeBase::GrabHandAx()
{
	// ?????? ??????
	mammothFootStepPlayTime += GetWorld()->DeltaTimeSeconds;

	if (mammothFootStepPlayTime >= 1.0f)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), footStepSound);
		mammothFootStepPlayTime = 0;
	}

	if (player->grabComp->bisGrabFistAxeR == true)
	{
		// UI ????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? ???? ?? ????
			howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToHunt, Param);

			// ?????? UI ????
			handAxUI->Destroy();

			// ?????? ???? ??????
			nextDelayTime = 0;

			SetState(EFlowState::HowToHunt);
		}
	}
}

void ASJ_WoogaGameModeBase::HowToHunt()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 9.0f)
	{
		// UI ?? ????
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// ?????? ????
				boar = GetWorld()->SpawnActor<ASJ_Character_Boar>(bpRunboar, Param);

				// ?????? ????
				mammothSpawn = GetWorld()->SpawnActor<ASJ_Actor_MammothSpawnDestroy>(bpMammothSpawn, Param);

				// ???? ????????
				TArray<AActor*> bpDeer;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASJ_Actor_RunDeer::StaticClass(), bpDeer);

				for (int i = 0; i < bpDeer.Num(); i++)
				{
					ASJ_Actor_RunDeer* emptyDeer = nullptr;
					deers.Add(emptyDeer);
				}
				for (int i = 0; i < bpDeer.Num(); i++)
				{
					auto deer = Cast<ASJ_Actor_RunDeer>(bpDeer[i]);
					deers[i] = deer;
					deers[i]->RunDeer();
				}

				// ?????????? ??????
				bIsDelay = false;

				howToNarTime = 0;
				nextDelayTime = 0;

				SetState(EFlowState::RunBoar);
			}
		}
	}
}


void ASJ_WoogaGameModeBase::RunBoar()
{
	if (boar->boarState == EBoarState::SlowMotion)
	{
		// ?????? ???? UI
		hitBoarUI = GetWorld()->SpawnActor<ASJ_Actor_HitBoarUI>(bpHitBoarUI, Param);

		SetState(EFlowState::HitBoar);
	}
}

void ASJ_WoogaGameModeBase::HitBoar()
{
	if (boar->boarState == EBoarState::Die)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			// ?????? UI ????
			hitBoarUI->Destroy();

			// ???????? ?????? UI
			// makeHandAxUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHandAxUI>(bpMakeHandAxUI, Param);

			// ???????? ?????? ???? ???? ????
			// makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

			// ???????? ???? ?????? ????
			slicePig->SetActorHiddenInGame(false);

			howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeHandAx, Param);

			mammoth = Cast<ASJ_Actor_Mammoth>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_Mammoth::StaticClass()));

			if (mammoth)
			{
				mammoth->isStateIn = true;
			}

			SetState(EFlowState::HowToMakeHandAx);
		}
	}
}

void ASJ_WoogaGameModeBase::MakeHandAx()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			makeHandAxUI->Destroy();

			howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeHandAx, Param);

			nextDelayTime = 0;

			SetState(EFlowState::HowToMakeHandAx);
		}
	}
}

void ASJ_WoogaGameModeBase::HowToMakeHandAx()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 9.0f)
	{
		// UI ?? ????
		if (player->isClose == true)
		{
			bIsDelay = true;
			isHandAxDelay = true;
		}
		// if (bIsDelay == true)
		if(isHandAxDelay == true)
		{
			handAxDelayTime += GetWorld()->DeltaTimeSeconds;

			if (handAxDelayTime >= 2.0f)
			{
				// ???????? UI ????
				indirectUI = GetWorld()->SpawnActor<ASJ_Actor_IndirectHitUI>(bpIndirectUI, Param);

				// ???? ??????
				hitPoint = GetWorld()->SpawnActor<AActor>(bpHitPoint, FVector(8081, 9232, 1247), FRotator(0, 0, 0), Param);

				fistAxe->bisStartBreak = true;

				// ?????????? ??????
				bIsDelay = false;

				handAxDelayTime = 0;

				nextDelayTime = 0;
				howToNarTime = 0;

				SetState(EFlowState::IndirectnessHit);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::IndirectHit()
{
	if (fistAxe->bisD1 == true)
	{
		// UI ??????
		bIsUIClose = true;
		hitPoint->SetActorHiddenInGame(true);

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???????? UI ???? 
			directUI = GetWorld()->SpawnActor<ASJ_Actor_DirectHitUI>(bpDirectHitUI, Param);

			// ???? UI ????
			indirectUI->Destroy();

			// ?????????? ??????
			nextDelayTime = 0;

			SetState(EFlowState::DirectlyHit);
		}
	}
}
void ASJ_WoogaGameModeBase::DirectHit()
{
	if (fistAxe->bisD15 == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;


		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			directUI->Destroy();

			// ?????????? ??????
			nextDelayTime = 0;

			// ???????? ???????? ????
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpHandAxHologram, Param);

			SetState(EFlowState::CompleteHandAx);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteHandAx()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 13)
	{
		// ???? ?????????? ????
		//goToGuideLine->Destroy();
		//makeHandAxRange->Destroy();

		// ???? ???? UI ????
		cuttingPigUI = GetWorld()->SpawnActor<ASJ_Actor_CuttingPigUI>(bpCuttingPigUI, Param);

		cutting->SetActorHiddenInGame(false);
		//	cuttingTwo->SetActorHiddenInGame(false);
		// sliceMeat->SetActorHiddenInGame(false);

		//?????? ???? ??????
		nextDelayTime = 0;

		// moveSpine->canMove = true;

		SetState(EFlowState::CuttingPig);
	}
}
#pragma endregion

#pragma  region FireUse
void ASJ_WoogaGameModeBase::CuttingPig()
{
	// ???? ???? ???? ???? ?????? ???? ????
	pigCutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));

	if (pigCutting->bisfinish == true)
	{
		// UI ??????
		bIsUIClose = true;

		tomahowk->SetActorHiddenInGame(false);

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ?????????? ????
			goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpFIreUseGuideLine, Param);

			slicePig->Destroy();
			// sliceMeat->Destroy();
			cutting->Destroy();
			// cuttingTwo->Destroy();

			// ???? ???????? UI????
			pickUpMeatUI = GetWorld()->SpawnActor<ASJ_Actor_PickUpMeatUI>(bpPickUpMeatUI, Param);

			FVector fireStrawPosition = FVector(6423, 7152, 1185);
			FRotator fireStrawRotation = FRotator(0, 0, 0);

			// ???? ?????? ?????? ?????? ????????
			fireStraw = GetWorld()->SpawnActor<AFireStraw>(bpFireStraw, fireStrawPosition, fireStrawRotation, Param);

			// ?????? ???? ???? ?????? ???? ???????? ???? ???? ???? ???? ????
			fireStraw->bisReadyFire = true;
			fireStraw->bisOverlab = false;
			fireStraw->bisSmog = false;
			fireStraw->isClear = false;

			// ???? UI ????
			//cuttingPigUI->Destroy();
			// ???? ????
			//makeHandAxRange->Destroy();

			moveSpine->canMove = true;

			// ?????? ???? ??????
			nextDelayTime = 0;

			SetState(EFlowState::GoToFireUse);
		}
	}
}

void ASJ_WoogaGameModeBase::GoToFireUse()
{
	// ?????????? ?????? ???? ???? ?? ?? ??????
	if (player->grabComp->bisTomahowkL == true || player->grabComp->bisTomahowkR == true)
	{
		moveSpine->canMove = true;
	}

	if (goToGuideLine->isTrigger == true)
	{
		// ???? ???????? UI ????
		pickUpMeatUI->Destroy();

		// ???? ???? UI ????
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpFireUseTitle, Param);

		moveSpine->canMove = false;

		SetState(EFlowState::FireUseTitle);
	}
}

void ASJ_WoogaGameModeBase::FireUseTitle()
{
	// ???? ?????? ????
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ?????????? ??????
		goToGuideLine->Destroy();

		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToFireUse, Param);

		// ?????????? ??????
		nextDelayTime = 0;

		SetState(EFlowState::HowToFireUse);
	}
}
void ASJ_WoogaGameModeBase::HowToFireUse()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 10.0f)
	{
		// UI ?? ????
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				fireStraw->outLine->SetVisibility(true);
				// ???? ???? ?????????? UI ????
				fireTwoUI = GetWorld()->SpawnActor<ASJ_Actor_FireTwoUI>(bpFireTwoUI, Param);

				moveSpine->canMove = true;

				// ?????????? ??????
				bIsDelay = false;
				nextDelayTime = 0;
				howToNarTime = 0;

				SetState(EFlowState::FiringTwo);
			}
		}
	}
}
void ASJ_WoogaGameModeBase::FiringTwo()
{
	if (fireStraw->isClear == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			cookUI = GetWorld()->SpawnActor<ASJ_Actor_CookUI>(bpCookUI, Param);
			// ?????? ???? ??????
			nextDelayTime = 0;
			tomahowk->bCanBake = true;

			// ???? UI ????
			fireTwoUI->Destroy();

			SetState(EFlowState::CookMeat);
		}
	}
}
void ASJ_WoogaGameModeBase::CookMeat()
{
	if (tomahowk->bisWelldone == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			eatMeatUI = GetWorld()->SpawnActor<ASJ_Actor_EatMeatUI>(bpEatMeatUI, Param);
			// ?????? ???? ??????
			nextDelayTime = 0;
			// ???? UI ????
			cookUI->Destroy();

			SetState(EFlowState::EatMeat);
		}
	}
}
void ASJ_WoogaGameModeBase::EatMeat()
{
	if (tomahowk->bisEat == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???????? ???? 
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpFireUseHologram, Param);

			// ?????? ???? ??????
			nextDelayTime = 0;

			// ???? UI ????
			eatMeatUI->Destroy();

			SetState(EFlowState::CompleteFireUse);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteFireUse()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 16)
	{
		// ?????????? ??????????
		goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpSpearGuideLine, Param);

		// ???? ???? ?????????? UI
		grabTomahowk = GetWorld()->SpawnActor<ASJ_Actor_GrabTomahowkUI>(bpGrabTomahowkUI, Param);

		// ?????? ???? ??????
		nextDelayTime = 0;

		SetState(EFlowState::GoToSpear);
	}
}

void ASJ_WoogaGameModeBase::GoToSpear()
{
	// moveSpine->canMove = true;

	if (goToGuideLine->isTrigger == true)
	{
		// ???? UI ????
		grabTomahowk->Destroy();
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpSpearTitle, Param);

		moveSpine->canMove = false;

		SetState(EFlowState::SpearTitle);
	}
}
#pragma  endregion

#pragma region SpearFunction
void ASJ_WoogaGameModeBase::SpearTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeSpear, Param);

		goToGuideLine->Destroy();

		// ?????? ???? ??????
		nextDelayTime = 0;

		// goToGuideLine->Destroy();
		SetState(EFlowState::HowTomakeSpear);
	}
}

void ASJ_WoogaGameModeBase::HowToMakeSpear()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 14.0f)
	{
		// UI ?? ????
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// ???? ???? ????
				makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

				// ?????????? ???? UI
				makeSpearUI = GetWorld()->SpawnActor<ASJ_Actor_MakeSpearUI>(bpMakeSpearUI, Param);

				// ?????????? ??????
				bIsDelay = false;
				nextDelayTime = 0;
				howToNarTime = 0;

				moveSpine->canMove = true;

				SetState(EFlowState::MakeSpear);
			}
		}
	}
}

void ASJ_WoogaGameModeBase::MakeSpear()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ?????????? 
			sumjjiRock = Cast<ASumjjiRock>(UGameplayStatics::GetActorOfClass(GetWorld(), ASumjjiRock::StaticClass()));
			sumjjiRock->outLine->SetVisibility(true);

			makeSpearUI->Destroy();

			// ???? ?????? ??????????UI ????
			breakStoneUI = GetWorld()->SpawnActor<ASJ_Actor_BreakStoneUI>(bpBreakStoneUI, Param);

			// ?????? ????
			nextDelayTime = 0;

			SetState(EFlowState::TakeRock);
		}
	}
}

// ?? ??????
void ASJ_WoogaGameModeBase::TakeRock()
{
	if (sumjjiRock->bisRockFin == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			breakStoneUI->Destroy();

			// ???? ???? UI ????
			connectSpearUI = GetWorld()->SpawnActor<ASJ_Actor_ConnectSpearUI>(bpConnectSpearUI, Param);

			cable = Cast<ACable>(UGameplayStatics::GetActorOfClass(GetWorld(), ACable::StaticClass()));
			// ???????? ??????
			cable->outLine->SetVisibility(true);

			// ?????? ???? ??????
			nextDelayTime = 0;

			SetState(EFlowState::ConnectSpear);
		}
	}
}

// ???? ????????
void ASJ_WoogaGameModeBase::ConnectSpear()
{
	if (cable->bIsConnect == true)
	{
		// UI ??????
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			connectSpearUI->Destroy();

			tieSpearUI = GetWorld()->SpawnActor<ASJ_Actor_TieSpearUI>(bpTieSpearUI, Param);

			string = Cast<AString>(UGameplayStatics::GetActorOfClass(GetWorld(), AString::StaticClass()));

			string->outLine->SetVisibility(true);

			nextDelayTime = 0;

			SetState(EFlowState::TieSpear);
		}
	}
}

// ???? ????
void ASJ_WoogaGameModeBase::TieSpear()
{
	if (cable->bIsTie == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			tieSpearUI->Destroy();

			makeHandAxRange->Destroy();

			// ???????? ????
			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpSpearHologram, Param);

			// ?????? ???? ??????
			nextDelayTime = 0;

			SetState(EFlowState::CompleteSpear);
		}
	}
}

void ASJ_WoogaGameModeBase::CompleteSpear()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 13)
	{
		// ???? ????
		makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpMakeHandAxRange, Param);

		// ?????? ???? UI
		huntFishUI = GetWorld()->SpawnActor<ASJ_Actor_HuntFishUI>(bpHuntFishUI, Param);

		// moveSpine->canMove = true;

		// ?????? ???? ??????
		nextDelayTime = 0;
		SetState(EFlowState::HuntFish);
	}
}

void ASJ_WoogaGameModeBase::HuntFish()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		bIsUIClose = true;
		// moveSpine->canMove = false;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			// huntFishUI->Destroy();
			huntFishUI->SetActorHiddenInGame(true);

			catchFishUI = GetWorld()->SpawnActor<ASJ_Actor_CatchFishUI>(bpCatchFishUI, Param);
			// ???? ??????
			catchFish = Cast<ASJ_Actor_CatchFish>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_CatchFish::StaticClass()));
			catchFish->outlineFish->SetVisibility(true);

			// ?????????? ??????
			nextDelayTime = 0;
			SetState(EFlowState::CatchFish);
		}
	}
}

void ASJ_WoogaGameModeBase::CatchFish()
{
	if (catchFish->isAttacked == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			catchFish->Destroy();

			goFryFishUI = GetWorld()->SpawnActor<ASJ_Actor_GoFryFishUI>(bpGoFryFishUI, Param);

			makeHandAxRange = GetWorld()->SpawnActor<ASJ_Actor_MakeRange>(bpGoToFry, Param);

			moveSpine->canMove = true;

			// ?????????? ??????
			nextDelayTime = 0;
			SetState(EFlowState::GoBackFireStraw);
		}
	}
}
void ASJ_WoogaGameModeBase::GoBackFireStraw()
{
	if (freeMove->bisFreeMove == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		player->moveComp->bisMove = false;

		if (nextDelayTime >= 1.0f)
		{
			goFryFishUI->Destroy();

			// ???? ???? ???? UI
			systemUI = GetWorld()->SpawnActor<ASJ_Actor_SystemUI>(bpFreeMoveUI, Param);

			// ?????????? ??????
			nextDelayTime = 0;
			SetState(EFlowState::CanFreeMove);
		}
	}
}
void ASJ_WoogaGameModeBase::CanFreeMove()
{
	systemUIDelayTime += GetWorld()->DeltaTimeSeconds;

	if (systemUIDelayTime >= 4.0f)
	{
		// ???? UI?? ????,
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
	}

	// ?????? ??????
	if (bIsDelay == true)
	{
		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		// 3?? ???? ?????? ???? ??????.
		// ???????? ???? ?????? ????????.
		if (nextDelayTime >= 1.0f)
		{
			// ?????? ???? ???? ???????? UI ???? ????
			player->moveComp->bisMove = true;

			// ?????? ???? ??????
			bIsDelay = false;
			nextDelayTime = 0;
			systemUIDelayTime = 0;

			SetState(EFlowState::GoToCookFish);
		}
	}
}
void ASJ_WoogaGameModeBase::GoToCookFish()
{
	if (makeHandAxRange->isPlayerIn == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			// makeHandAxRange->Destroy();

			cookFishUI = GetWorld()->SpawnActor<ASJ_Actor_CookFishUI>(bpCookFishUI, Param);
			// ?????? ???? ??????
			nextDelayTime = 0;
			SetState(EFlowState::CookFish);
		}
	}
}

void ASJ_WoogaGameModeBase::CookFish()
{
	if (cable->bisWelldone == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;

		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			cookFishUI->Destroy();

			// ???? ?????? ???? UI
			eatFishUI = GetWorld()->SpawnActor<ASJ_Actor_EatFishUI>(bpEatFishUI, Param);

			// ?????? ???? ??????
			nextDelayTime = 0;
			SetState(EFlowState::EatFish);
		}

	}
}
void ASJ_WoogaGameModeBase::EatFish()
{
	if (cable->bisEat == true)
	{
		bIsUIClose = true;

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			// ???? UI ????
			eatFishUI->Destroy();

			// ???? ?????????? UI
			goToHutUI = GetWorld()->SpawnActor<ASJ_Actor_GoToHutUI>(bpGoToHutUI, Param);

			// ?????? ???? ??????
			nextDelayTime = 0;
			SetState(EFlowState::SpawnHutGuideLine);
		}
	}
}

#pragma  endregion

#pragma region HutFuntion
void ASJ_WoogaGameModeBase::SpawnHutGuideLine()
{
	// ???? ??????????
	goToGuideLine = GetWorld()->SpawnActor<ASJ_Actor_GoToGuideLine>(bpHutGuideLine, Param);

	SetState(EFlowState::GoToHut);
}
void ASJ_WoogaGameModeBase::GoToHut()
{
	if (goToGuideLine->isTrigger == true)
	{
		// ???? UI ????
		// goToHutUI->Destroy();

		moveSpine->canMove = false;

		// ???? ????
		title = GetWorld()->SpawnActor<ASJ_Actor_Title>(bpHutTitle, Param);

		player->moveComp->bisMove = false;

		SetState(EFlowState::HutTitle);
	}
}
void ASJ_WoogaGameModeBase::HutTitle()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 6.0f)
	{
		// ?????????? UI ????
		howToFlow = GetWorld()->SpawnActor<ASJ_Actor_HowToFlow>(bpHowToMakeHut, Param);

		lastHouse->SetActorHiddenInGame(false);

		// ?????????? ????
		goToGuideLine->Destroy();

		// ?????? ???? ??????
		nextDelayTime = 0;

		SetState(EFlowState::HowToMakeHut);
	}
}
void ASJ_WoogaGameModeBase::HowToMakeHut()
{
	howToNarTime += GetWorld()->DeltaTimeSeconds;
	if (howToNarTime >= 4.0f)
	{
		// UI ?? ????
		if (player->isClose == true)
		{
			bIsDelay = true;
		}
		if (bIsDelay == true)
		{
			nextDelayTime += GetWorld()->DeltaTimeSeconds;

			if (nextDelayTime >= 1.0f)
			{
				// ?????????? UI ????
				makeHutUI = GetWorld()->SpawnActor<ASJ_Actor_MakeHutUI>(bpMakeHutUI, Param);

				TArray<AActor*> bpStick;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStick::StaticClass(), bpStick);

				if (bpStick.Num() > 0)
				{
					for (int i = 0; i < bpStick.Num(); i++)
					{
						AStick* emptyStick = nullptr;
						sticks.Add(emptyStick);
					}

					for (int i = 0; i < bpStick.Num(); i++)
					{
						auto sstick = Cast<AStick>(bpStick[i]);
						sticks[i] = sstick;
						sticks[i]->outLine->SetVisibility(true);
					}
				}
				lastHouse->bisAttachStart = true;
				// ?????????? ??????
				bIsDelay = false;
				nextDelayTime = 0;
				howToNarTime = 0;

				player->moveComp->bisMove = true;

				SetState(EFlowState::MakeHut);
			}
		}
	}
}
void ASJ_WoogaGameModeBase::MakeHut()
{
	if (lastHouse->isUIDown == true)
	{
		makeHutUI->SetActorHiddenInGame(true);
	}

	if (lastHouse->bisClear == true)
	{
		bIsUIClose = true;
		

		nextDelayTime += GetWorld()->DeltaTimeSeconds;
		if (nextDelayTime >= 1.0f)
		{
			makeHutUI->Destroy();

			hologram = GetWorld()->SpawnActor<ASJ_Hologram>(bpHutHologram, Param);

			// ?????? ???? ??????
			nextDelayTime = 0;

			SetState(EFlowState::CompleteHut);
		}
	}
}
void ASJ_WoogaGameModeBase::CompleteHut()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 18)
	{
		// ?????? ???? ??????
		nextDelayTime = 0;

		SetState(EFlowState::OutGame);
	}
}

void ASJ_WoogaGameModeBase::OutGame()
{
	nextDelayTime += GetWorld()->DeltaTimeSeconds;

	if (nextDelayTime >= 7.0f)
	{
		UGameplayStatics::OpenLevel(this, TEXT("NSJ_Outro"));
	}
}

#pragma endregion

