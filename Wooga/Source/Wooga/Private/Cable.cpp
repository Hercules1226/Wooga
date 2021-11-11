// Fill out your copyright notice in the Description page of Project Settings.


#include "Cable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

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
	
	
	nia = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("Niagara")));
	if (nia)
	{
		//nia->SetHiddenInGame(false);
	}
}

// Called every frame
void ACable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

