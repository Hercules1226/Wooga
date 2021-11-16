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

// Sets default values
ASJ_Character_Boar::ASJ_Character_Boar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boarMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BoarMesh"));
	boarMesh->SetupAttachment(GetCapsuleComponent());

	hitPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitPoint"));
	hitPoint->SetupAttachment(boarMesh);
}

// Called when the game starts or when spawned
void ASJ_Character_Boar::BeginPlay()
{
	Super::BeginPlay();

	anim = Cast<USJ_BoarAnimInstance>(boarMesh->GetAnimInstance());

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	hitPoint->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Character_Boar::HitPointTrigger);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Character_Boar::HitBoarBody);

	hitPoint->SetHiddenInGame(true);

	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector p = FVector(7010.0f, 6000.0f, 1200.0f);

	SetActorLocation(p);

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
	// 돼지 위치
	me = GetActorLocation();
	// 플레이어 위치
	playerLoc = player->GetActorLocation();
	// 돼지가 플레이어를 바라보게
	dir = playerLoc - me;
	// 정규화
	dir.Normalize();

	FVector p = me + dir * speed * GetWorld()->DeltaTimeSeconds;

	SetActorLocation(p);

	// FRotator r = FRotator(GetActorRotation().Pitch, dir.Rotation().Yaw, GetActorRotation().Roll);
	SetActorRotation(dir.Rotation());

	float slowRange = FVector::Dist(me, playerLoc);

	if (slowRange <= distance)
	{
		CustomTimeDilation = 0.05f;
		hitPoint->SetHiddenInGame(false);
		

		SetState(EBoarState::SlowMotion);
	}
}

void ASJ_Character_Boar::SlowMotion()
{
}

void ASJ_Character_Boar::Hit()
{
	// 벽방향으로 날라가야 한다.
	me = GetActorLocation();
	dir = GetActorRightVector();

	FVector p1 = me + dir * GetWorld()->DeltaTimeSeconds * 1500.f;

	SetActorLocation(p1);
}

void ASJ_Character_Boar::Die()
{
	Destroy();
}

void ASJ_Character_Boar::HitPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	fistAxe = Cast<AFistAxe>(OtherActor);

	// 만약 슬로우 모션 상태이고
	if (boarState == EBoarState::SlowMotion)
	{
		// 돼지를 주먹도끼로 쳤으면
		if (fistAxe)
		{
			CustomTimeDilation = 1.0f;
			anim->isHit = true;
			GetCapsuleComponent()->SetEnableGravity(true);

			UGameplayStatics::PlaySound2D(GetWorld(), pigDieSound);
			SetState(EBoarState::Hit);
		}
	}
}

void ASJ_Character_Boar::HitBoarBody(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto hitRock = Cast<ASJ_Actor_BoarHitRock>(OtherActor);

	if (boarState == EBoarState::Hit)
	{
		if (OtherActor == hitRock)
		{
			isHitBoar = true;
			hitPoint->SetHiddenInGame(true);
			SetState(EBoarState::Die);
		}
	}
}

