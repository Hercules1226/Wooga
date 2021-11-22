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

	
	if(player->camLoc)
	{
	FVector dir = player->camLoc->GetRelativeLocation() - rootComp->GetRelativeLocation();
	dir.Normalize();
	SetActorRotation(dir.ToOrientationRotator());
	}
	


	
	 if (bisEnd == false)
	{
		GetWorld()->SpawnActor<AIcon1>(icon1Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon2>(Icon2Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon3>(Icon3Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon4>(Icon4Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon5>(Icon5Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon6>(Icon6Factory, GetTransform());

		watch->SetHiddenInGame(true);

		bisEnd = true;
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
		// 불의 활용
		if (knowledgePoint == 0)
		{
			// 진동효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			// 머티리얼 변경
			watch->SetMaterial(0, watchOneMaterial);
			SetState(EBlinkState::Blink);

			knowledgePoint = 1;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
		// 채집
		if (knowledgePoint == 1)
		{
			// 진동효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchTwoMaterial);
			SetState(EBlinkState::Blink);

			knowledgePoint = 2;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
		// 주먹도끼
		if (knowledgePoint == 2)
		{
			// 진동효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchThreeMaterial);
			SetState(EBlinkState::Blink);

			knowledgePoint = 3;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
		// 불의 활용
		if (knowledgePoint == 3)
		{
			// 진동효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchFourMaterial);
			SetState(EBlinkState::Blink);

			knowledgePoint = 4;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
		// 슴베찌르개
		if (knowledgePoint == 4)
		{
			// 진동효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchFiveMaterial);
			SetState(EBlinkState::Blink);

			knowledgePoint = 5;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
		// 움집
		if (knowledgePoint == 5)
		{
			// 진동효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchSixMaterial);
			SetState(EBlinkState::Blink);

			knowledgePoint = 6;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
	}
}
// 지식이 들어오면 T_Base, TW_icon 텍스쳐 변경 -> 머티리얼 변경으로 대체
// Amount 값을 0.1로 바로 변경 -> 시간이 지나면 다시 0으로 시간은 6초
// Boost는 3초 동안 30으로 가야함 나머지 3초동안 0으로 다시 감 
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

