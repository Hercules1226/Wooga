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

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	boarMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boar"));
	boarMesh->SetupAttachment(rootComp);

	hitPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitPoint"));
	hitPoint->SetupAttachment(boarMesh);
}

// Called when the game starts or when spawned
void ASJ_Actor_RunBoar::BeginPlay()
{
	Super::BeginPlay();

	FVector p = FVector(8190.0f, 7190.0f, 1160.0f);

	SetActorLocation(p);
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	hitPoint->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_RunBoar::OnTrigger);

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
	// ���� ��ġ
	me = GetActorLocation();
	// �÷��̾� ��ġ
	playerLoc = player->GetActorLocation();
	// ������ �÷��̾ �ٶ󺸰�
	dir = playerLoc - me;
	// ����ȭ
	dir.Normalize();

	FVector p = me + dir * speed * GetWorld()->DeltaTimeSeconds;

	SetActorLocation(p);
	SetActorRotation(dir.Rotation());

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
	// ���������� ���󰡾� �Ѵ�.
	me = GetActorLocation();
	dir = GetActorRightVector();

	FVector p1 = me + dir * GetWorld()->DeltaTimeSeconds * -600.f;

	SetActorLocation(p1);
}

void ASJ_Actor_RunBoar::Die()
{
	
}

void ASJ_Actor_RunBoar::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	fistAxe = Cast<AFistAxe>(OtherActor);

	FString name = OtherActor->GetName();

	// ���� ���ο� ��� �����̰�
	if (boarState == EBoarState::SlowMotion)
	{
		// ������ �ָԵ����� ������
		if (fistAxe)
		{
			CustomTimeDilation = 1.0f;
			SetState(EBoarState::Hit);
		}
	}

	if (boarState == EBoarState::Hit)
	{
		if (name.Contains("rock"))
		{
			SetState(EBoarState::Die);
		}
	}
}

