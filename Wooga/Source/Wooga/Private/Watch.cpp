// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"
#include "Icon1.h"
#include "Icon2.h"
#include "Icon3.h"
#include "Icon4.h"
#include "Icon5.h"
#include "Icon6.h"

// Sets default values
AWatch::AWatch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(rootComp);

	watch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Watch"));
	watch->SetupAttachment(rootComp);

	part1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part1"));
	//part1->SetupAttachment(rootComp);

	part2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part2"));
	//part2->SetupAttachment(rootComp);

	part3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part3"));
	//part3->SetupAttachment(rootComp);

	part4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part4"));
	//part4->SetupAttachment(rootComp);

	part5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part5"));
	//part5->SetupAttachment(rootComp);

	part6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Part6"));
	//part6->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void AWatch::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	icon1 = Cast<AIcon1>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon1::StaticClass()));

	icon2 = Cast<AIcon2>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon2::StaticClass()));

	icon3 = Cast<AIcon3>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon3::StaticClass()));

	icon4 = Cast<AIcon4>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon4::StaticClass()));

	icon5 = Cast<AIcon5>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon5::StaticClass()));

	icon6 = Cast<AIcon6>(UGameplayStatics::GetActorOfClass(GetWorld(), AIcon6::StaticClass()));


	watch->OnComponentBeginOverlap.AddDynamic(this, &AWatch::InKnowledgePoint);
}

// Called every frame
void AWatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (blinkFlow)
	{
	case EBlinkState::Idle:
		Idle();
		break;
	case EBlinkState::Blink:
		Blink();
		break;
	case EBlinkState::UnBlink:
		UnBlink();
		break;
	}


	if (player->camLoc)
	{
		FVector dir1 = player->camLoc->GetRelativeLocation() - part1->GetRelativeLocation();
		dir1.Normalize();
		SetActorRotation(dir1.ToOrientationRotator());

		FVector dir2 = player->camLoc->GetRelativeLocation() - part2->GetRelativeLocation();
		dir2.Normalize();
		SetActorRotation(dir2.ToOrientationRotator());

		FVector dir3 = player->camLoc->GetRelativeLocation() - part3->GetRelativeLocation();
		dir3.Normalize();
		SetActorRotation(dir3.ToOrientationRotator());

		FVector dir4 = player->camLoc->GetRelativeLocation() - part4->GetRelativeLocation();
		dir4.Normalize();
		SetActorRotation(dir4.ToOrientationRotator());

		FVector dir5 = player->camLoc->GetRelativeLocation() - part5->GetRelativeLocation();
		dir5.Normalize();
		SetActorRotation(dir5.ToOrientationRotator());

		FVector dir6 = player->camLoc->GetRelativeLocation() - part6->GetRelativeLocation();
		dir6.Normalize();
		SetActorRotation(dir6.ToOrientationRotator());
	}




	if (bisEnd == false)
	{
		currentTime += DeltaTime;
		if (currentTime >= 5.f)
		{
			GetWorld()->SpawnActor<AIcon1>(icon1Factory, GetTransform());
			GetWorld()->SpawnActor<AIcon2>(Icon2Factory, GetTransform());
			GetWorld()->SpawnActor<AIcon3>(Icon3Factory, GetTransform());
			GetWorld()->SpawnActor<AIcon4>(Icon4Factory, GetTransform());
			GetWorld()->SpawnActor<AIcon5>(Icon5Factory, GetTransform());
			GetWorld()->SpawnActor<AIcon6>(Icon6Factory, GetTransform());

			/*watch->SetHiddenInGame(true);*/

			bisEnd = true;
		}
	}



}

EBlinkState AWatch::GetState()
{
	return EBlinkState();
}

void AWatch::SetState(EBlinkState state)
{
	blinkFlow = state;
}

void AWatch::InKnowledgePoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto fireEvent = Cast<AFireEvent>(OtherActor);

	if (OtherActor == fireEvent)
	{
		// ???? ????
		if (knowledgePoint == 0)
		{
			// ????????
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			// ???????? ????
			watch->SetMaterial(0, watchOneMaterial);
			SetState(EBlinkState::Blink);

			//isKnowledgeIn = true;
			OtherActor->Destroy();
			knowledgePoint = 1;
		}
		// ????
		if (knowledgePoint == 1)
		{
			// ????????
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchTwoMaterial);
			SetState(EBlinkState::Blink);
			
			//isKnowledgeIn = true;
			OtherActor->Destroy();
			knowledgePoint = 2;
		}
		// ????????
		if (knowledgePoint == 2)
		{
			// ????????
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchThreeMaterial);
			SetState(EBlinkState::Blink);
			
			//isKnowledgeIn = true;
			OtherActor->Destroy();
			knowledgePoint = 3;
		}
		// ???? ????
		if (knowledgePoint == 3)
		{
			// ????????
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchFourMaterial);
			SetState(EBlinkState::Blink);
			
			//isKnowledgeIn = true;
			OtherActor->Destroy();
			knowledgePoint = 4;
		}
		// ??????????
		if (knowledgePoint == 4)
		{
			// ????????
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchFiveMaterial);
			SetState(EBlinkState::Blink);
			
			//isKnowledgeIn = true;
			OtherActor->Destroy();
			knowledgePoint = 5;
		}
		// ????
		if (knowledgePoint == 5)
		{
			// ????????
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchSixMaterial);
			SetState(EBlinkState::Blink);
			
			//isKnowledgeIn = true;
			OtherActor->Destroy();
			knowledgePoint = 6;
		}
	}
}
// ?????? ???????? T_Base, TW_icon ?????? ???? -> ???????? ???????? ????
// Amount ???? 0.1?? ???? ???? -> ?????? ?????? ???? 0???? ?????? 6??
// Boost?? 3?? ???? 30???? ?????? ?????? 3?????? 0???? ???? ?? 
void AWatch::Blink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	watch->SetScalarParameterValueOnMaterials(TEXT("Amount"), 0.1f);

	float boostBlink = FMath::Lerp(0.0f, 30.0f, playTime);

	watch->SetScalarParameterValueOnMaterials(TEXT("Boost"), boostBlink);

	if (playTime >= 3.0f)
	{
		playTime = 0;

		SetState(EBlinkState::UnBlink);
	}
}

void AWatch::UnBlink()
{
	playTime += GetWorld()->DeltaTimeSeconds;

	float unBoostBlink = FMath::Lerp(30.0f, 0.0f, playTime);

	watch->SetScalarParameterValueOnMaterials(TEXT("Boost"), unBoostBlink);

	if (playTime >= 3.0f)
	{
		playTime = 0;
		watch->SetScalarParameterValueOnMaterials(TEXT("Amount"), 0.0f);

		SetState(EBlinkState::Idle);
	}
}

void AWatch::Idle()
{

}

