// Fill out your copyright notice in the Description page of Project Settings.


#include "Watch.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "FireEvent.h"

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

	watch->OnComponentBeginOverlap.AddDynamic(this, &AWatch::InKnowledgePoint);
}

// Called every frame
void AWatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (blinkFlow)
	{
	case EBlinkState::Idle:
		OnOpacity();
		break;
	case EBlinkState::Blink:
		PlayOpacity();
		break;
	case EBlinkState::UnBlink:
		OffOpacity();
		break;
	}

	if(player->camLoc)
	{
	FVector dir = player->camLoc->GetRelativeLocation() - rootComp->GetRelativeLocation();
	dir.Normalize();
	SetActorRotation(dir.ToOrientationRotator());
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
			// 진동효과
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

			watch->SetMaterial(0, watchOneMaterial);


			knowledgePoint = 1;
			isKnowledgeIn = true;
			OtherActor->Destroy();
		}
	}
}
// 지식이 들어오면 T_Base, TW_icon 텍스쳐 변경 -> 머티리얼 변경으로 대체
// Amount 값을 0.1로 바로 변경 -> 시간이 지나면 다시 0으로 시간은 6초
// Boost는 3초 동안 30으로 가야함 나머지 3초동안 0으로 다시 감 

void AWatch::OnOpacity()
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

void AWatch::PlayOpacity()
{
}

void AWatch::OffOpacity()
{
}

