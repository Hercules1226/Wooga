// Fill out your copyright notice in the Description page of Project Settings.


#include "IconSpot.h"
#include "Components/StaticMeshComponent.h"
#include "Icon1.h"
#include "Icon2.h"
#include "Icon3.h"
#include "Icon4.h"
#include "Icon5.h"
#include "Icon6.h"

// Sets default values
AIconSpot::AIconSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	spot1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot1"));
	spot1->SetupAttachment(rootComp);

	spot2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot2"));
	spot2->SetupAttachment(rootComp);

	spot3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot3"));
	spot3->SetupAttachment(rootComp);

	spot4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot4"));
	spot4->SetupAttachment(rootComp);

	spot5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot5"));
	spot5->SetupAttachment(rootComp);

	spot6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot6"));
	spot6->SetupAttachment(rootComp);

	spotIcon1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon1"));
	spotIcon1->SetupAttachment(spot1);

	spotIcon2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon2"));
	spotIcon2->SetupAttachment(spot2);

	spotIcon3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon3"));
	spotIcon3->SetupAttachment(spot3);

	spotIcon4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon4"));
	spotIcon4->SetupAttachment(spot4);

	spotIcon5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon5"));
	spotIcon5->SetupAttachment(spot5);

	spotIcon6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Icon6"));
	spotIcon6->SetupAttachment(spot6);
}

// Called when the game starts or when spawned
void AIconSpot::BeginPlay()
{
	Super::BeginPlay();
	
	spot1->OnComponentBeginOverlap.AddDynamic(this, &AIconSpot::OnCollisionEnter);
	spot2->OnComponentBeginOverlap.AddDynamic(this, &AIconSpot::OnCollisionEnter);
	spot3->OnComponentBeginOverlap.AddDynamic(this, &AIconSpot::OnCollisionEnter);
	spot4->OnComponentBeginOverlap.AddDynamic(this, &AIconSpot::OnCollisionEnter);
	spot5->OnComponentBeginOverlap.AddDynamic(this, &AIconSpot::OnCollisionEnter);
	spot6->OnComponentBeginOverlap.AddDynamic(this, &AIconSpot::OnCollisionEnter);
}

// Called every frame
void AIconSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIconSpot::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto icon1 = Cast<AIcon1>(OtherActor);
	auto icon2 = Cast<AIcon2>(OtherActor);
	auto icon3 = Cast<AIcon3>(OtherActor);
	auto icon4 = Cast<AIcon4>(OtherActor);
	auto icon5 = Cast<AIcon5>(OtherActor);
	auto icon6 = Cast<AIcon6>(OtherActor);

	if (OverlappedComp == spot1 && OtherActor == icon1)
	{
		spot1->SetHiddenInGame(false);
		spotIcon1->SetHiddenInGame(false);
	}

	if (OverlappedComp == spot2 && OtherActor == icon2)
	{
		spot2->SetHiddenInGame(false);
		spotIcon2->SetHiddenInGame(false);
	}

	if (OverlappedComp == spot3 && OtherActor == icon3)
	{
		spot3->SetHiddenInGame(false);
		spotIcon3->SetHiddenInGame(false);
	}

	if (OverlappedComp == spot4 && OtherActor == icon4)
	{
		spot4->SetHiddenInGame(false);
		spotIcon4->SetHiddenInGame(false);
	}

	if (OverlappedComp == spot5 && OtherActor == icon5)
	{
		spot5->SetHiddenInGame(false);
		spotIcon5->SetHiddenInGame(false);
	}

	if (OverlappedComp == spot6 && OtherActor == icon6)
	{
		spot6->SetHiddenInGame(false);
		spotIcon6->SetHiddenInGame(false);
	}
}

