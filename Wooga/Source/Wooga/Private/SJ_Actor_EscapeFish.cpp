// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_EscapeFish.h"
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "SJ_Actor_CatchFish.h"
#include "SJ_EscapeFishAnimInstance.h"

// Sets default values
ASJ_Actor_EscapeFish::ASJ_Actor_EscapeFish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	fish = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Fish"));
	fish->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ASJ_Actor_EscapeFish::BeginPlay()
{
	Super::BeginPlay();
	
	catchFish = Cast<ASJ_Actor_CatchFish>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_CatchFish::StaticClass()));

	escapeFishAnimInst = Cast<USJ_EscapeFishAnimInstance>(fish->GetAnimInstance());

	currentTime = FMath::RandRange(0.1f, 2.0f);
}

// Called every frame
void ASJ_Actor_EscapeFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 아직 공격 받기 전 이라면, 
	if (catchFish->isAttacked == false)
	{
		currentTime += DeltaTime;
		if (isTurn == false)
		{
			// 1 초간 앞으로 이동 하고
			me = GetActorLocation();

			FVector p1 = me + GetActorForwardVector() * swimSpeed * DeltaTime;

			SetActorLocation(p1);
		}
		
		// 1초가 지나면 0.3초 기다린 후 회전한다.

		if (currentTime >= 2.5f)
		{
			isTurn = true;
			turnTime += DeltaTime;

			if (turnTime >= 1.0f)
			{
				FRotator r1 = GetActorRotation() + FRotator(0, 180, 0);
				SetActorRotation(r1);
				isTurn = false;
				currentTime = 0;
				turnTime = 0;
			}
		}
	}

	if (catchFish->isAttacked == true)
	{
		me = GetActorLocation();
		target = catchFish->GetActorLocation();

		dir = -(target - me);
		dir.Normalize();

		FVector p2 = GetActorLocation() + GetActorForwardVector() * runSpeed * DeltaTime;

		SetActorLocation(p2);

		// SetActorRotation(dir.Rotation());

		escapeFishAnimInst->isRun = true;

		destroyTime += DeltaTime;

		if (destroyTime >= 3.0f)
		{
			destroyTime = 0;
			Destroy();
		}
	}
}

