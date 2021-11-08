// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_MammothSpawnDestroy.h"
#include <Components/BoxComponent.h>
#include "SJ_Actor_Mammoth.h"

// Sets default values
ASJ_Actor_MammothSpawnDestroy::ASJ_Actor_MammothSpawnDestroy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp =CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	spawnRange = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnRange"));
	spawnRange->SetupAttachment(rootComp);

	destroyRange = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyRange"));
	destroyRange->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_MammothSpawnDestroy::BeginPlay()
{
	Super::BeginPlay();
	
	FVector p = FVector(5749, 7421, 1390);
	SetActorLocation(p);

	FRotator r = FRotator(0, 50, 0);
	SetActorRotation(r);

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	mammoth = GetWorld()->SpawnActor<ASJ_Actor_Mammoth>(bpMammoth,spawnRange->GetComponentLocation(),spawnRange->GetComponentRotation(), Param);

	destroyRange->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_MammothSpawnDestroy::TriggerIn);
}

// Called every frame
void ASJ_Actor_MammothSpawnDestroy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_MammothSpawnDestroy::TriggerIn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndeawx, bool bFromSweep, const FHitResult& SweepResult)
{
	mammoth = Cast<ASJ_Actor_Mammoth>(OtherActor);

	if (mammoth)
	{
		mammoth->Destroy();
	}
}

