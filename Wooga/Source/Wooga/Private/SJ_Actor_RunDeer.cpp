// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_RunDeer.h"
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "SJ_Actor_DeerTurnAndDestroy.h"
#include <Components/BoxComponent.h>

// Sets default values
ASJ_Actor_RunDeer::ASJ_Actor_RunDeer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	deer = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Deer"));
	deer->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_RunDeer::BeginPlay()
{
	Super::BeginPlay();

	isTurn = true;
}

// Called every frame
void ASJ_Actor_RunDeer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	turnAndDestory = Cast<ASJ_Actor_DeerTurnAndDestroy>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_DeerTurnAndDestroy::StaticClass()));

	if (isTurn == true)
	{
		me = GetActorLocation();
		turnPoint = turnAndDestory->turnPoint->GetComponentLocation();
		dir = turnPoint - me;
		dir.Normalize();

		FVector p = me + GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(p);

		SetActorRotation(dir.Rotation());
	}
	
	if (isDestroy == true)
	{
		me = GetActorLocation();
		diePoint = turnAndDestory->destroyPoint->GetComponentLocation();
		dir = diePoint - me;
		dir.Normalize();

		FVector p1 = me + dir * speed * DeltaTime;
		SetActorLocation(p1);

		SetActorRotation(dir.Rotation());
	}

}

