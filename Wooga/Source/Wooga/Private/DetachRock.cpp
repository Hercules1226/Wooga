// Fill out your copyright notice in the Description page of Project Settings.


#include "DetachRock.h"
#include "HalfRock.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADetachRock::ADetachRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);
}

// Called when the game starts or when spawned
void ADetachRock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADetachRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADetachRock::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	halfRock = Cast<AHalfRock>(OtherActor);
	if (OtherActor == halfRock)
	{
		Destroy();
	}
}

