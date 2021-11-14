// Fill out your copyright notice in the Description page of Project Settings.


#include "Cable.h"
#include "String.h"
#include "SumjjiRock.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACable::ACable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	stickComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stick Component"));
	SetRootComponent(stickComp);

	cableComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cable Component"));
	cableComp->SetupAttachment(stickComp);

	rockComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock Component"));
	rockComp->SetupAttachment(stickComp);

	handComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hand Component"));
	handComp->SetupAttachment(stickComp);

	splineComp = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	splineComp->SetupAttachment(stickComp);

	onMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("On Material"));

	offMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Off Material"));

	//nia = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia"));
}

// Called when the game starts or when spawned
void ACable::BeginPlay()
{
	Super::BeginPlay();
	stickComp->OnComponentBeginOverlap.AddDynamic(this, &ACable::OnCollisionEnter);
	rockComp->OnComponentBeginOverlap.AddDynamic(this, &ACable::OnCollisionEnter);

	//string = Cast<AString>(UGameplayStatics::GetActorOfClass(GetWorld(), AString::StaticClass()));
}

// Called every frame
void ACable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACable::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	nia = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("Spiral_2")));
	string = Cast<AString>(OtherActor);
	sumjjiRock = Cast<ASumjjiRock>(OtherActor);

	if (bisSumjjiRock == true)
	{
		if (OtherActor == string)
		{
			if (nia)
			{
				//nia->SetActive(true);
				cableComp->SetHiddenInGame(false);
			}
		}
	}

	if (OverlappedComp == rockComp && OtherActor == sumjjiRock)
	{
		rockComp->SetHiddenInGame(false);
		sumjjiRock->Destroy();
	}
}