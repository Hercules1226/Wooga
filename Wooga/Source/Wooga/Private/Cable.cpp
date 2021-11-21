// Fill out your copyright notice in the Description page of Project Settings.


#include "Cable.h"
#include "String.h"
#include "SumjjiRock.h"
#include "VR_Player.h"
#include "FireStraw.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include <Components/SkeletalMeshComponent.h>
#include "SJ_Actor_CatchFish.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
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

	outLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline"));
	outLine->SetupAttachment(stickComp);
	outLine->SetCollisionProfileName(TEXT("NoCollision"));

	fish = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Fish"));
	fish->SetupAttachment(stickComp);

	splineComp = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	splineComp->SetupAttachment(stickComp);

	onMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("On Material"));

	offMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Off Material"));

	welldone = CreateDefaultSubobject<UMaterial>(TEXT("Welldone"));

	//nia = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia"));
}

// Called when the game starts or when spawned
void ACable::BeginPlay()
{
	Super::BeginPlay();
	stickComp->OnComponentBeginOverlap.AddDynamic(this, &ACable::OnCollisionEnter);
	rockComp->OnComponentBeginOverlap.AddDynamic(this, &ACable::OnCollisionEnter);
	sumjjiRock = Cast<ASumjjiRock>(UGameplayStatics::GetActorOfClass(GetWorld(), ASumjjiRock::StaticClass()));
	catchFish = Cast<ASJ_Actor_CatchFish>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Actor_CatchFish::StaticClass()));

	outLine->SetVisibility(false);
}

// Called every frame
void ACable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (biscatch == true)
	{
		currentTime += GetWorld()->DeltaTimeSeconds;
		if (currentTime >= 5.f)
		{
			/*fish->SetCollisionProfileName(TEXT("Ragdoll"));
			fish->SetSimulatePhysics(true);*/
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("FIIIIIIIIIIIIIIIIIIIIIIIIIIIsh!!")));

			fish->SetActive(false);
			currentTime = 0.f;
			biscatch = false;
		}
	}

	if (bisOverlab == true)
	{
		currentTime += GetWorld()->DeltaTimeSeconds;

		if (currentTime >= 3.f)
		{
			fish->SetMaterial(0, welldone);
			bisWelldone = true;
			bisOverlab = false;
			//disTime += GetWorld()->DeltaTimeSeconds;
			//blend = FMath::Lerp(0.f, 1.f, disTime * 0.5f);

		//	meshComp1->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);
		}
	}
}

void ACable::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	nia = Cast<UNiagaraComponent>(GetDefaultSubobjectByName(TEXT("Niagara")));
	string = Cast<AString>(OtherActor);
	
	auto fireStraw = Cast<AFireStraw>(OtherActor);
	auto player = Cast<AVR_Player>(OtherActor);
	//catchFish = Cast<ASJ_Actor_CatchFish>(OtherActor);

	if (OtherActor == string)
	{
		//nia->SetHiddenInGame(false);
			//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnEffect, cableComp->GetComponentLocation(), cableComp->GetComponentRotation());
		string->Destroy();
		cableComp->SetMaterial(0, offMaterial);

		bIsTie = true;
	}

	if (OverlappedComp == rockComp && OtherActor == sumjjiRock)
	{
		rockComp->SetHiddenInGame(false);
		cableComp->SetHiddenInGame(false);
		rockComp->SetMaterial(0, onMaterial);
		sumjjiRock->Destroy();

		bIsConnect = true;
	}

	if (OtherActor == fireStraw)
	{
		bisOverlab = true;
		currentTime = 0.f;
	}


	if (bisWelldone == true)
	{
		if (player)
		{
			if (OtherComp == player->mouthComp)
			{
				FVector location = this->GetActorLocation();
				UGameplayStatics::PlaySound2D(GetWorld(), eatSound);
				fish->SetHiddenInGame(true);
			}
		}
	}
}