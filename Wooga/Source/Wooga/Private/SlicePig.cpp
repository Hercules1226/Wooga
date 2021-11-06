// Fill out your copyright notice in the Description page of Project Settings.


#include "SlicePig.h"
#include "Cutting.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ASlicePig::ASlicePig()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	pigHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pig Head"));
	pigHead->SetupAttachment(rootComp);

	top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));

	bottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bottom"));

	inside = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Inside"));
}

// Called when the game starts or when spawned
void ASlicePig::BeginPlay()
{
	Super::BeginPlay();

	cutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));

	topPos = top->GetRelativeLocation();
	targetTopPos = top->GetRelativeLocation() + FVector(0.f, 0.f, 20.f) * 3.f;

	bottomPos = bottom->GetRelativeLocation();
	targetBottomPos = bottom->GetRelativeLocation() + FVector(0.f, 0.f, -20.f) * 3.f;

	topRot = top->GetRelativeRotation();
	targetTopRot = top->GetRelativeRotation() + FRotator(-1.f, 0.f, 0.f) * 3.f;

	bottomRot = bottom->GetRelativeRotation();
	targetBottomRot = bottom->GetRelativeRotation() + FRotator(-2.f, 0.f, 0.f) * 3.f;
}

// Called every frame
void ASlicePig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cutting->bisfinish == true)
	{
		topPos = FMath::Lerp(topPos, targetTopPos, GetWorld()->DeltaTimeSeconds * 2);
		bottomPos = FMath::Lerp(bottomPos, targetBottomPos, GetWorld()->DeltaTimeSeconds * 2);

		/*topRot = FMath::Lerp(topRot, targetTopRot, GetWorld()->DeltaTimeSeconds * 2);
		bottomRot = FMath::Lerp(bottomRot, targetBottomRot, GetWorld()->DeltaTimeSeconds * 2);*/

		top->SetRelativeLocation(topPos);
		//top->SetRelativeRotation(topRot);
		bottom->SetRelativeLocation(bottomPos);
		//bottom->SetRelativeRotation(bottomRot);

	}
}

