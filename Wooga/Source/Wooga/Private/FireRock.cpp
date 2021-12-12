// Fill out your copyright notice in the Description page of Project Settings.


#include "FireRock.h"
#include "FireRock2.h"
#include "VR_Player.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AFireRock::AFireRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);

	// 물리 관련 설정
	boxComp->SetSimulatePhysics(true);
	boxComp->SetEnableGravity(true);
	boxComp->SetCollisionProfileName(TEXT("PickUp"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);

	outLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline"));
	outLine->SetupAttachment(meshComp);
	outLine->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AFireRock::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AFireRock::OnCollisionEnter);
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	fireRock2 = Cast<AFireRock2>(UGameplayStatics::GetActorOfClass(GetWorld(), AFireRock2::StaticClass()));

	outLine->SetVisibility(false);
}

// Called every frame
void AFireRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (bisOverlab == true)
	{
		myPos = FMath::Lerp(myPos, returnKnockbackPos, 5.f * GetWorld()->DeltaTimeSeconds);
		myPos2 = FMath::Lerp(myPos2, returnKnockbackPos2, 5.f * GetWorld()->DeltaTimeSeconds);
		player->leftHand->SetRelativeLocation(myPos);
		player->rightHand->SetRelativeLocation(myPos2);

		// 물어보기
		if (FVector::Dist(myPos, returnKnockbackPos) < 1.f)
		{
			bisOverlab = false;
		}

		if (FVector::Dist(myPos2, returnKnockbackPos2) < 1.f)
		{
			bisOverlab = false;
		}
	}
}

void AFireRock::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (currentTime >= 0.3f)
	{
		if (fireRock2)
		{
			if (OtherComp == fireRock2->boxComp)
			{
				myPos = player->leftHand->GetRelativeLocation();
				knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;

				myPos2 = player->rightHand->GetRelativeLocation();
				knockbackPos2 = player->rightHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;

				myPos = knockbackPos;
				myPos2 = knockbackPos2;

				player->leftHand->SetRelativeLocation(myPos);
				player->rightHand->SetRelativeLocation(myPos2);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorLocation() + FVector(0.f, 0.0f, -30.f));

				bisOverlab = true;

				// Sound

				location = this->GetActorLocation();
				rotation = this->GetActorRotation();

				UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
				overlabCount++;

				currentTime = 0.0f;
			}
		}
	}
}

//  myPos, knock, 

