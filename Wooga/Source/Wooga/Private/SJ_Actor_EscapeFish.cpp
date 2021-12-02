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
}

// Called every frame
void ASJ_Actor_EscapeFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (catchFish->isAttacked == true)
	{
		FVector me = GetActorLocation();
		FVector target = catchFish->GetActorLocation();

		FVector dir = -(target - me);
		dir.Normalize();

		FVector p = GetActorLocation() + GetActorForwardVector() * speed * DeltaTime;

		SetActorLocation(p);

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

