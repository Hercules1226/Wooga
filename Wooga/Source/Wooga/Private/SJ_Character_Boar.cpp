// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Character_Boar.h"
#include <Components/CapsuleComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"
#include "FistAxe.h"
#include "SJ_BoarAnimInstance.h"
#include "SJ_Actor_BoarHitRock.h"
#include "SlicePig.h"
#include "SJ_Actor_Hammer.h"
#include "DetachRock.h"
#include <Components/AudioComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include "SJ_Actor_PigTurnPoint.h"
#include <Components/CapsuleComponent.h> 

// Sets default values
ASJ_Character_Boar::ASJ_Character_Boar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boarMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BoarMesh"));
	boarMesh->SetupAttachment(GetCapsuleComponent());

	hitPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitPoint"));
	hitPoint->SetupAttachment(boarMesh);

	hammer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hammer"));
	hammer->SetupAttachment(boarMesh);

	hitPointFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitPointFX"));
	hitPointFX->SetupAttachment(boarMesh);

	runSound = CreateDefaultSubobject<UAudioComponent>(TEXT("RunAudio"));
}

// Called when the game starts or when spawned
void ASJ_Character_Boar::BeginPlay()
{
	Super::BeginPlay();

	anim = Cast<USJ_BoarAnimInstance>(boarMesh->GetAnimInstance());

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	turnPoint = Cast<ASJ_Actor_PigTurnPoint>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_PigTurnPoint::StaticClass()));

	hitPoint->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Character_Boar::HitPointTrigger);
	boarMesh->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Character_Boar::HitBoarBody);

	hitPoint->SetHiddenInGame(true);
	hitPointFX->SetHiddenInGame(true);

	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector p = FVector(7374, 7026, 1285);

	SetActorLocation(p);

	// Ÿ�� ����Ʈ �󱼿� �ٿ��ֱ�
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	hitPoint->AttachToComponent(boarMesh, attachRules, TEXT("HitPosition"));
	hitPointFX->AttachToComponent(boarMesh, attachRules, TEXT("HitPosition"));

	SetState(EBoarState::Run);
}

// Called every frame
void ASJ_Character_Boar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (boarState)
	{
	case EBoarState::Run:
		Run();
		break;
	case EBoarState::SlowMotion:
		SlowMotion();
		break;
	case EBoarState::Hit:
		Hit();
		break;
	case EBoarState::Die:
		Die();
		break;
	}
}

// Called to bind functionality to input
void ASJ_Character_Boar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASJ_Character_Boar::SetState(EBoarState state)
{
	boarState = state;
}

EBoarState ASJ_Character_Boar::GetState()
{
	return EBoarState();
}

void ASJ_Character_Boar::Run()
{
	if (isTurn == false)
	{
		me = GetActorLocation();
		turnPointLoc = turnPoint->GetActorLocation();
		dir = turnPointLoc - me;
		dir.Normalize();

		FVector p1 = me + dir * speed * GetWorld()->DeltaTimeSeconds;

		SetActorLocation(p1);

		SetActorRotation(dir.Rotation());
	}
	if (isTurn == true)
	{
		// ���� ��ġ
		me = GetActorLocation();
		// �÷��̾� ��ġ
		playerLoc = player->capsuleComp->GetComponentLocation();
		// ������ �÷��̾ �ٶ󺸰�
		dir = playerLoc - me;
		// ����ȭ
		dir.Normalize();

		FVector p2= me + dir * speed * GetWorld()->DeltaTimeSeconds;

		SetActorLocation(p2);

		// FRotator r = FRotator(GetActorRotation().Pitch, dir.Rotation().Yaw, GetActorRotation().Roll);

		// FRotator r = GetActorRotation() + dir.Rotation() * speed * GetWorld()->DeltaTimeSeconds;
		SetActorRotation(dir.Rotation());
	}
	
	float slowRange = FVector::Dist(me, playerLoc);

	if (slowRange <= distance)
	{
		distTime += GetWorld()->DeltaTimeSeconds;
		if (distTime >= 0.2f)
		{
			CustomTimeDilation = 0.05f;
			//hitPoint->SetHiddenInGame(false);
			hitPointFX->SetHiddenInGame(false);

			distTime = 0;

			runSound->Stop();
			SetState(EBoarState::SlowMotion);
		}
	}
}

void ASJ_Character_Boar::SlowMotion()
{
}

void ASJ_Character_Boar::Hit()
{
	// ���������� ���󰡾� �Ѵ�.
	me = GetActorLocation();

	dir = GetActorRightVector();


	FVector p1 = me + dir * GetWorld()->DeltaTimeSeconds * 1300;

	// GetCapsuleComponent()->SetRelativeLocation(p1);

	SetActorLocation(p1);

	curRot = GetActorRotation();
	setRot = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 30.0f);

	curRot = FMath::Lerp(curRot, setRot, GetWorld()->DeltaTimeSeconds * 5);

	// SetActorRotation(curRot);
}

void ASJ_Character_Boar::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Die"));
	Destroy();
}

void ASJ_Character_Boar::HitPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	fistAxe = Cast<AFistAxe>(OtherActor);

	// ���� ���ο� ��� �����̰�
	if (boarState == EBoarState::SlowMotion)
	{
		// ������ �ָԵ����� ������
		if (fistAxe)
		{
			CustomTimeDilation = 1.0f;
			anim->isHit = true;
			boarMesh->SetCollisionProfileName(TEXT("Ragdoll"));
			boarMesh->SetSimulatePhysics(true);
			// boarMesh->AddForce(GetActorRightVector() * 1000000);

			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			GetWorld()->SpawnActor<ASJ_Actor_Hammer>(bpHammer, Param);

			hitPoint->SetHiddenInGame(true);

			UGameplayStatics::PlaySound2D(GetWorld(), pigDieSound);
			SetState(EBoarState::Hit);
		}
	}
}

void ASJ_Character_Boar::HitBoarBody(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto hitRock = Cast<ASJ_Actor_BoarHitRock>(OtherActor);
	auto detachRock = Cast<ADetachRock>(OtherActor);

	if (boarState == EBoarState::Hit)
	{
		if (OtherActor == hitRock || OtherActor == detachRock)
		{
			isHitBoar = true;
			
			SetState(EBoarState::Die);
		}
	}
}

