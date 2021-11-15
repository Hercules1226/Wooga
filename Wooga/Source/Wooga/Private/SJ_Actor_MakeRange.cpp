// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_MakeRange.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "VR_Player.h"
// Sets default values
ASJ_Actor_MakeRange::ASJ_Actor_MakeRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	range = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	SetRootComponent(range);

	footStep = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FootStep"));
	footStep->SetupAttachment(range);
}

// Called when the game starts or when spawned
void ASJ_Actor_MakeRange::BeginPlay()
{
	Super::BeginPlay();
	
	range->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_MakeRange::OnPlayerOverlap);
}

// Called every frame
void ASJ_Actor_MakeRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_MakeRange::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (OtherActor == player)
	{
		isPlayerIn = true;

		UE_LOG(LogTemp, Warning, TEXT("PlayerIn"));
	}
}

