// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_PlayerMoveStopPoint.h"
#include <Components/BoxComponent.h>
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>
#include "MoveSpline.h"

// Sets default values
ASJ_Actor_PlayerMoveStopPoint::ASJ_Actor_PlayerMoveStopPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	point = CreateDefaultSubobject<UBoxComponent>(TEXT("Point"));
	SetRootComponent(point);
}

// Called when the game starts or when spawned
void ASJ_Actor_PlayerMoveStopPoint::BeginPlay()
{
	Super::BeginPlay();
	
	point->OnComponentBeginOverlap.AddDynamic(this,  &ASJ_Actor_PlayerMoveStopPoint::PlayerOverlap);

	moveSpline = Cast<AMoveSpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMoveSpline::StaticClass()));
}

// Called every frame
void ASJ_Actor_PlayerMoveStopPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_PlayerMoveStopPoint::PlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (OtherActor == player)
	{
		moveSpline->canMove = false;
		Destroy();
	}
}

