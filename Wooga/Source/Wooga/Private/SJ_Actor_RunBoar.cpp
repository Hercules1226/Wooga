// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_RunBoar.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"
#include "FistAxe.h"

// Sets default values
ASJ_Actor_RunBoar::ASJ_Actor_RunBoar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boarMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boar"));
	SetRootComponent(boarMesh);

	hitPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitPoint"));
	hitPoint->SetupAttachment(boarMesh);
}

// Called when the game starts or when spawned
void ASJ_Actor_RunBoar::BeginPlay()
{
	Super::BeginPlay();

	FVector p = FVector(7010.0f, 6000.0f, 1200.0f);

	SetActorLocation(p);
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	boarMesh->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_RunBoar::BoarTrigger);

	hitPoint->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_RunBoar::HitPointTrigger);

	hitPoint->SetHiddenInGame(true);

	SetState(EBoarState::Run);
}

// Called every frame
void ASJ_Actor_RunBoar::Tick(float DeltaTime)
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

void ASJ_Actor_RunBoar::SetState(EBoarState state)
{
	boarState = state;
}

EBoarState ASJ_Actor_RunBoar::GetState()
{
	return EBoarState();
}

void ASJ_Actor_RunBoar::Run()
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

	FRotator r = FRotator(GetActorRotation().Pitch, dir.Rotation().Yaw, GetActorRotation().Roll);
	// SetActorRotation(dir.Rotation().Yaw);

	float slowRange = FVector::Dist(me, playerLoc);

	if (slowRange <= distance)
	{
		CustomTimeDilation = 0.05f;
		hitPoint->SetHiddenInGame(false);

		SetState(EBoarState::SlowMotion);
	}
}

void ASJ_Actor_RunBoar::SlowMotion()
{
	
}

void ASJ_Actor_RunBoar::Hit()
{
	// 벽방향으로 날라가야 한다.
	me = GetActorLocation();
	dir = GetActorRightVector();

	FVector p1 = me + dir * GetWorld()->DeltaTimeSeconds * 600.f;

	SetActorLocation(p1);
}

void ASJ_Actor_RunBoar::Die()
{
	
}

void ASJ_Actor_RunBoar::HitPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	fistAxe = Cast<AFistAxe>(OtherActor);

	FString name = OtherActor->GetName();

	// 만약 슬로우 모션 상태이고
	if (boarState == EBoarState::SlowMotion)
	{
		// 돼지를 주먹도끼로 쳤으면
		if (fistAxe)
		{
			CustomTimeDilation = 1.0f;
			SetState(EBoarState::Hit);
		}
	}
}

void ASJ_Actor_RunBoar::BoarTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString name = OtherActor->GetName();

	if (boarState == EBoarState::Hit)
	{
		if (name.Contains("rock"))
		{
			// SetState(EBoarState::Die);
		}
	}
}

