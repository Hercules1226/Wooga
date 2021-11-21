// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_CatchFish.h"
#include <Components/SkeletalMeshComponent.h>
#include "SJ_CatchFishAnimInstance.h"
#include "Cable.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ASJ_Actor_CatchFish::ASJ_Actor_CatchFish()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fish = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Fish"));
	SetRootComponent(fish);

	outlineFish = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OutLine"));
	outlineFish->SetupAttachment(fish);
}

// Called when the game starts or when spawned
void ASJ_Actor_CatchFish::BeginPlay()
{
	Super::BeginPlay();
	sumjji = Cast<ACable>(UGameplayStatics::GetActorOfClass(GetWorld(), ACable::StaticClass()));

	fish->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_CatchFish::OnOverlap);

	catchFishAnimInst = Cast<USJ_CatchFishAnimInstance>(fish->GetAnimInstance());
}

// Called every frame
void ASJ_Actor_CatchFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_CatchFish::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//sumjji = Cast<ACable>(OtherActor);

	if (OtherComp == sumjji->rockComp)
	{
		// ½¿º£Âî¸£°³¿¡ Âñ¸®¸é
		catchFishAnimInst->isDie = true;
		isAttacked = true;

		outlineFish->SetVisibility(false);

		fish->SetHiddenInGame(true);
		sumjji->fish->SetHiddenInGame(false);
		sumjji->biscatch = true;
		sumjji->currentTime = 0.f;
		//Destroy();
	}
}

