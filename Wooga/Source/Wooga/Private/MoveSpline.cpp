// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSpline.h"
#include "MoveActorComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMoveSpline::AMoveSpline()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	spline->SetupAttachment(root);

	spline->bDrawDebug = true;
	spline->Duration = totalPathTimeController;
	totalPathTimeController = 0.0f;
	bcanMoveActor = false;
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMoveSpline::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	if (actorToMoveClass != nullptr)
	{
		actorToMove = GetWorld()->SpawnActor<AActor>(actorToMoveClass, spline->GetComponentTransform());
	}
	if (actorToMove != nullptr)
	{
		startTime = GetWorld()->GetTimeSeconds();
		bcanMoveActor = true;
	}
}

// Called every frame
void AMoveSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	curTime += DeltaTime;

	if (canMove == true)
	{
		if (timeOn == true)
		{
			moveTime += GetWorld()->DeltaTimeSeconds;
		}
	}

	if ((actorToMove != nullptr) && (bcanMoveActor))
	{
		currentSplineTime = (moveTime / totalPathTimeController);
		currentSplineTimeRot = ((GetWorld()->GetTimeSeconds()) / totalPathTimeController);
		/*if (3.f > curTime)
		{
			timeOn = true;
		}

		else if (3.f <= curTime && 6.f > curTime)
		{
			timeOn = false;
		}

		else if (6.f <= curTime)
		{
			timeOn = true;
		}*/

		distance = spline->GetSplineLength() * currentSplineTime;
		distanceRot = spline->GetSplineLength() * currentSplineTimeRot;

		FVector position = spline->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
		actorToMove->SetActorLocation(position);

		FVector direction = spline->GetDirectionAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);

		FRotator rotator = direction.Rotation();
		actorToMove->SetActorRotation(rotator);


	}


}

