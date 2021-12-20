// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_ChangeFreeMove.h"
#include <Components/BoxComponent.h>
#include "VR_Player.h"
#include "SJ_WoogaGameModeBase.h"
#include "MoveActorComponent.h"
#include <Kismet/GameplayStatics.h>
#include "MoveSpline.h"

// Sets default values
ASJ_ChangeFreeMove::ASJ_ChangeFreeMove()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	range = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	SetRootComponent(range);
}

// Called when the game starts or when spawned
void ASJ_ChangeFreeMove::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());
	moveSpline = Cast<AMoveSpline>(UGameplayStatics::GetActorOfClass(GetWorld(), AMoveSpline::StaticClass()));
	
	range->OnComponentBeginOverlap.AddDynamic(this, &ASJ_ChangeFreeMove::OnPlayerIn);
}

// Called every frame
void ASJ_ChangeFreeMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	curTime += DeltaTime;

	if (bisFreeMove == true)
	{
		if (curTime >= 2.0f)
		{
			Destroy();
		}
	}
}

void ASJ_ChangeFreeMove::OnPlayerIn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (OtherActor == player)
	{
		moveSpline->lastMove = true;
		bisFreeMove = true;
	}
}

