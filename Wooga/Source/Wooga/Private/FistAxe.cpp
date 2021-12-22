// Fill out your copyright notice in the Description page of Project Settings.


#include "FistAxe.h"
#include "DetachRock.h"
#include "HalfRock.h"
#include "VR_Player.h"
#include "Cutting.h"
#include "GrabActorComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "SJ_WoogaGameModeBase.h"

// Sets default values
AFistAxe::AFistAxe()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fist = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fist"));
	SetRootComponent(fist);

	halfRock = CreateDefaultSubobject<UChildActorComponent>(TEXT("HalfRock"));
	halfRock->SetupAttachment(fist);

	rock2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock2"));
	rock2->SetupAttachment(fist);

	rock3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock3"));
	rock3->SetupAttachment(fist);

	rock4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock4"));
	rock4->SetupAttachment(fist);

	rock5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock5"));
	rock5->SetupAttachment(fist);

	rock6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock6"));
	rock6->SetupAttachment(fist);

	rock7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock7"));
	rock7->SetupAttachment(fist);

	rock8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock8"));
	rock8->SetupAttachment(fist);

	rock9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock9"));
	rock9->SetupAttachment(fist);

	rock10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock10"));
	rock10->SetupAttachment(fist);

	rock11 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock11"));
	rock11->SetupAttachment(fist);

	rock12 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock12"));
	rock12->SetupAttachment(fist);

	rock13 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock13"));
	rock13->SetupAttachment(fist);

	rock14 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock14"));
	rock14->SetupAttachment(fist);

	rock15 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock15"));
	rock15->SetupAttachment(fist);

	faGrabPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FAGrabPoint"));
	faGrabPoint->SetupAttachment(fist);

	handHologramL = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandHologramL"));
	handHologramL->SetupAttachment(fist);

	handHologramR = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandHologramR"));
	handHologramR->SetupAttachment(fist);

	fakeHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FakeHand"));
	fakeHand->SetupAttachment(fist);

	offMa = CreateDefaultSubobject<UMaterialInstance>(TEXT("Off Ma"));

	onMa = CreateDefaultSubobject<UMaterialInstance>(TEXT("On Ma"));
}

// Called when the game starts or when spawned
void AFistAxe::BeginPlay()
{
	Super::BeginPlay();

	fist->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock2->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock3->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock4->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock5->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock6->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock7->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock8->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock9->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock10->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock11->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock12->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock13->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock14->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);
	rock15->OnComponentBeginOverlap.AddDynamic(this, &AFistAxe::OnCollisionEnter);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());
	//rock2->SetMaterial(0, onMaterial);

	handHologramL->SetHiddenInGame(true);
	handHologramR->SetHiddenInGame(true);
	fakeHand->SetHiddenInGame(true);
}

// Called every frame
void AFistAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//hr = Cast<AHalfRock>(UGameplayStatics::GetActorOfClass(GetWorld(), AHalfRock::StaticClass()));

	currentTime += DeltaTime;
	if (bisOverlab == true)
	{
		myPos = FMath::Lerp(myPos, returnKnockbackPos, 5.f * GetWorld()->DeltaTimeSeconds);
		player->leftHand->SetRelativeLocation(myPos);
		// 물어보기
		if (FVector::Dist(myPos, returnKnockbackPos) < 1.f)
		{
			bisOverlab = false;
		}
	}
}

void AFistAxe::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if (gameModeBase->flowState == EFlowState::IndirectnessHit || gameModeBase->flowState == EFlowState::DirectlyHit)
	{
		if (currentTime >= 1.f)
		{

			if (bisStartBreak == true)
			{
				detachRock = Cast<ADetachRock>(OtherActor);
				if (OtherActor == detachRock)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					rock2->SetMaterial(0, onMa);
					bisOverlab = true;
					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					childRock = Cast<AHalfRock>(halfRock->GetChildActor());
					childRock->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
					player->grabComp->RightReleaseAction();
					fakeHand->SetHiddenInGame(true);
					player->rightHand->SetHiddenInGame(false);
					handHologramR->SetHiddenInGame(true);
					bisD1 = true;

					halfRockComp = Cast<UStaticMeshComponent>(childRock->GetDefaultSubobjectByName(TEXT("halfRock")));
					halfRockComp->SetSimulatePhysics(true);
					halfRockComp->SetEnableGravity(true);

					currentTime = 0.f;
				}
			}

			if (bisD1 == true)
			{
				if (OverlappedComp == rock2 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock2->SetSimulatePhysics(true);
					rock2->SetEnableGravity(true);

					rock2->SetMaterial(0, offMa);
					rock3->SetMaterial(0, onMa);

					rock2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock2->DetachFromParent(true);
					currentTime = 0.f;

					bisD2 = true;

				}
			}

			if (bisD2 == true)
			{
				if (OverlappedComp == rock3 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock3->SetSimulatePhysics(true);
					rock3->SetEnableGravity(true);

					rock3->SetMaterial(0, offMa);
					rock4->SetMaterial(0, onMa);

					rock3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock3->DetachFromParent(true);
					currentTime = 0.f;

					bisD3 = true;

				}
			}

			if (bisD3 == true)
			{
				if (OverlappedComp == rock4 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock4->SetSimulatePhysics(true);
					rock4->SetEnableGravity(true);

					rock4->SetMaterial(0, offMa);
					rock5->SetMaterial(0, onMa);

					rock4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock4->DetachFromParent(true);
					currentTime = 0.f;

					bisD4 = true;

				}
			}

			if (bisD4 == true)
			{
				if (OverlappedComp == rock5 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock5->SetSimulatePhysics(true);
					rock5->SetEnableGravity(true);

					rock5->SetMaterial(0, offMa);
					rock6->SetMaterial(0, onMa);

					rock5->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock5->DetachFromParent(true);
					currentTime = 0.f;

					bisD5 = true;

				}
			}

			if (bisD5 == true)
			{
				if (OverlappedComp == rock6 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock6->SetSimulatePhysics(true);
					rock6->SetEnableGravity(true);

					rock6->SetMaterial(0, offMa);
					rock7->SetMaterial(0, onMa);

					rock6->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock6->DetachFromParent(true);
					currentTime = 0.f;

					bisD6 = true;

				}
			}

			if (bisD6 == true)
			{
				if (OverlappedComp == rock7 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock7->SetSimulatePhysics(true);
					rock7->SetEnableGravity(true);

					rock7->SetMaterial(0, offMa);
					rock8->SetMaterial(0, onMa);

					rock7->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock7->DetachFromParent(true);
					currentTime = 0.f;

					bisD7 = true;

				}
			}

			if (bisD7 == true)
			{
				if (OverlappedComp == rock8 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock8->SetSimulatePhysics(true);
					rock8->SetEnableGravity(true);

					rock8->SetMaterial(0, offMa);
					rock9->SetMaterial(0, onMa);

					rock8->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock8->DetachFromParent(true);
					currentTime = 0.f;

					bisD8 = true;

				}
			}

			if (bisD8 == true)
			{
				if (OverlappedComp == rock9 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock9->SetSimulatePhysics(true);
					rock9->SetEnableGravity(true);

					rock9->SetMaterial(0, offMa);
					rock10->SetMaterial(0, onMa);

					rock9->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock9->DetachFromParent(true);
					currentTime = 0.f;

					bisD9 = true;
				}
			}

			if (bisD9 == true)
			{
				if (OverlappedComp == rock10 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock10->SetSimulatePhysics(true);
					rock10->SetEnableGravity(true);

					rock10->SetMaterial(0, offMa);
					rock11->SetMaterial(0, onMa);

					rock10->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock10->DetachFromParent(true);
					currentTime = 0.f;

					bisD10 = true;
				}
			}

			if (bisD10 == true)
			{
				if (OverlappedComp == rock11 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock11->SetSimulatePhysics(true);
					rock11->SetEnableGravity(true);

					rock11->SetMaterial(0, offMa);
					rock12->SetMaterial(0, onMa);

					rock11->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock11->DetachFromParent(true);
					currentTime = 0.f;

					bisD11 = true;
				}
			}

			if (bisD11 == true)
			{
				if (OverlappedComp == rock12 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock12->SetSimulatePhysics(true);
					rock12->SetEnableGravity(true);

					rock12->SetMaterial(0, offMa);
					rock13->SetMaterial(0, onMa);

					rock12->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock12->DetachFromParent(true);
					currentTime = 0.f;

					bisD12 = true;
				}
			}

			if (bisD12 == true)
			{
				if (OverlappedComp == rock13 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock13->SetSimulatePhysics(true);
					rock13->SetEnableGravity(true);

					rock13->SetMaterial(0, offMa);
					rock14->SetMaterial(0, onMa);

					rock13->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock13->DetachFromParent(true);
					currentTime = 0.f;

					bisD13 = true;
				}
			}

			if (bisD13 == true)
			{
				if (OverlappedComp == rock14 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock14->SetSimulatePhysics(true);
					rock14->SetEnableGravity(true);

					rock14->SetMaterial(0, offMa);
					rock15->SetMaterial(0, onMa);

					rock14->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock14->DetachFromParent(true);
					currentTime = 0.f;

					bisD14 = true;
				}
			}

			if (bisD14 == true)
			{
				if (OverlappedComp == rock15 && OtherComp == halfRockComp)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					location = this->GetActorLocation();
					rotation = this->GetActorRotation();

					UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

					rock15->SetSimulatePhysics(true);
					rock15->SetEnableGravity(true);

					rock14->SetMaterial(0, offMa);
					rock15->SetMaterial(0, onMa);

					rock15->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock15->DetachFromParent(true);
					currentTime = 0.f;

					bisD15 = true;
				}
			}

			if (bisD15 == true)
			{
				rock15->SetMaterial(0, offMa);
				halfRock->SetHiddenInGame(true);
				player->grabComp->RightHalfRockReleaseAction();
				// UE_LOG(LogTemp, Warning, TEXT("CompleteHandAx"));
				
			}
		}
	}
}

