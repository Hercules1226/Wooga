// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_BoarSpawn.h"
#include <Components/BoxComponent.h>
#include "SJ_Actor_RunBoar.h"

// Sets default values
ASJ_Actor_BoarSpawn::ASJ_Actor_BoarSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	spawnRange = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnRange"));
	spawnRange->SetupAttachment(rootComp);

	slowRange = CreateDefaultSubobject<UBoxComponent>(TEXT("SlowRange"));
	slowRange->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_BoarSpawn::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	boar = GetWorld()->SpawnActor<ASJ_Actor_RunBoar>(bpBoar, spawnRange->GetComponentLocation(), spawnRange->GetComponentRotation() ,Param);
	
	slowRange->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_BoarSpawn::OnTrigger);
}

// Called every frame
void ASJ_Actor_BoarSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_BoarSpawn::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	boar = Cast<ASJ_Actor_RunBoar>(OtherActor);

	if (boar)
	{
		boar->CustomTimeDilation = 0.1f;
	}
}

