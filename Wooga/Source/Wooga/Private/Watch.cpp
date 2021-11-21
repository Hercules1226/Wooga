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

	/*
	if(player->camLoc)
	{
	FVector dir = player->camLoc->GetRelativeLocation() - rootComp->GetRelativeLocation();
	dir.Normalize();
	SetActorRotation(dir.ToOrientationRotator());
	}
	*/

	if (bisEnd == false)
	{
		GetWorld()->SpawnActor<AIcon1>(icon1Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon2>(Icon2Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon3>(Icon3Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon4>(Icon4Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon5>(Icon5Factory, GetTransform());
		GetWorld()->SpawnActor<AIcon6>(Icon6Factory, GetTransform());
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
		if (knowledgePoint == 0)
		{
			// ����ȿ��
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			// ��Ƽ���� ����
			watch->SetMaterial(0, watchOneMaterial);
			SetState(EBlinkState::Blink);

			knowledgePoint = 1;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
	}
}
// ������ ������ T_Base, TW_icon �ؽ��� ���� -> ��Ƽ���� �������� ��ü
// Amount ���� 0.1�� �ٷ� ���� -> �ð��� ������ �ٽ� 0���� �ð��� 6��
// Boost�� 3�� ���� 30���� ������ ������ 3�ʵ��� 0���� �ٽ� �� 
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

