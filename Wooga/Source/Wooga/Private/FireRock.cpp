// Fill out your copyright notice in the Description page of Project Settings.


#include "FireRock.h"
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

	// ���� ���� ����
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

	// outLine->SetVisibility(false);
}

// Called every frame
void AFireRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if (bisOverlab == false)
	{
		myPos = FMath::Lerp(myPos, returnKnockbackPos, 5.f * GetWorld()->DeltaTimeSeconds);
		player->leftHand->SetRelativeLocation(myPos);
		// �����
		if (FVector::Dist(myPos, returnKnockbackPos) < 1.f)
		{
			bisOverlab = true;
		}
	}

	if (overlabCount == 15)
	{
		
	}
}

void AFireRock::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	me = Cast<AFireRock>(OtherActor);

	if (me)
	{
		if (bisOverlab == true)
		{
			myPos = player->leftHand->GetRelativeLocation();
			knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
			myPos = knockbackPos;
			player->leftHand->SetRelativeLocation(myPos);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory, GetActorLocation() + FVector(0.f, 0.0f, 0.f));

			bisOverlab = false;

			// Sound
			
			location = me->GetActorLocation();
			rotation = me->GetActorRotation();

			UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
			overlabCount++;
		}
	}
}


