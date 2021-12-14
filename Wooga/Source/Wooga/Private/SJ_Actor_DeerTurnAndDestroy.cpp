// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_DeerTurnAndDestroy.h"
#include <Components/BoxComponent.h>
#include "SJ_Actor_RunDeer.h"

// Sets default values
ASJ_Actor_DeerTurnAndDestroy::ASJ_Actor_DeerTurnAndDestroy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	turnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("TurnPoint"));
	turnPoint->SetupAttachment(rootComp);

	destroyPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyPoint"));
	destroyPoint->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_DeerTurnAndDestroy::BeginPlay()
{
	Super::BeginPlay();
	
	turnPoint->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_DeerTurnAndDestroy::OnTurnPointTrigger);

	destroyPoint->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_DeerTurnAndDestroy::OnDestroyPointTrigger);
}

// Called every frame
void ASJ_Actor_DeerTurnAndDestroy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_DeerTurnAndDestroy::OnTurnPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto deer = Cast<ASJ_Actor_RunDeer>(OtherActor);

	if (deer)
	{
		UE_LOG(LogTemp, Warning, TEXT("DeerTurn"));
		deer->isTurn = false;
		deer->isDestroy = true;
	}
}

void ASJ_Actor_DeerTurnAndDestroy::OnDestroyPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto deer = Cast<ASJ_Actor_RunDeer>(OtherActor);

	if (OtherActor == deer)
	{
		OtherActor->Destroy();
	}
}

