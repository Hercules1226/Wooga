// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_PigTurnPoint.h"
#include <Components/BoxComponent.h>
#include "SJ_Character_Boar.h"

// Sets default values
ASJ_Actor_PigTurnPoint::ASJ_Actor_PigTurnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	point = CreateDefaultSubobject<UBoxComponent>(TEXT("Point"));
	SetRootComponent(point);
}

// Called when the game starts or when spawned
void ASJ_Actor_PigTurnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	point->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_PigTurnPoint::OnCollisionEnter);
}

// Called every frame
void ASJ_Actor_PigTurnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_PigTurnPoint::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto boar = Cast<ASJ_Character_Boar>(OtherActor);

	if (OtherActor == boar) 
	{
		boar->isTurn = true;
	}
}

