// Fill out your copyright notice in the Description page of Project Settings.


#include "Tomahowk.h"
#include "FireStraw.h"
#include "Components/BoxComponent.h"
#include "GrabActorComponent.h"
#include "VR_Player.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ATomahowk::ATomahowk()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);

	meshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component1"));
	meshComp1->SetupAttachment(meshComp);
	meshComp4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component4"));
	meshComp4->SetupAttachment(meshComp1);

	meatOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meat OutLine"));
	meatOutline->SetupAttachment(meshComp1);

	boneOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bone OutLine"));
	boneOutline->SetupAttachment(meshComp4);

	medium = CreateDefaultSubobject<UMaterialInstance>(TEXT("Medium"));
	welldone = CreateDefaultSubobject<UMaterialInstance>(TEXT("Welldone"));
}

// Called when the game starts or when spawned
void ATomahowk::BeginPlay()
{
	Super::BeginPlay();
	//meshComp->OnComponentBeginOverlap.AddDynamic(this, &ATomahowk::OnCollisionBoneEnter);
	meshComp1->OnComponentBeginOverlap.AddDynamic(this, &ATomahowk::OnCollisionEnter);
}

// Called every frame
void ATomahowk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bisOverlab == true)
	{
		currentTime += GetWorld()->DeltaTimeSeconds;

		if (currentTime >= 1.f)
		{
			meshComp1->SetMaterial(0, medium);

			if (bisBake == false)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), bakeSound);
				bisBake = true;
			}
			//disTime += GetWorld()->DeltaTimeSeconds;
			//blend = FMath::Lerp(0.f, 1.f, disTime * 0.5f);

		//	meshComp1->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);
		}

		if (currentTime >= 3.f)
		{
			meshComp1->SetMaterial(0, welldone);
			bisWelldone = true;
			/*disTime += GetWorld()->DeltaTimeSeconds;
			blend = FMath::Lerp(0.f, 1.f, disTime * 0.5f);*/

			//	meshComp1->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);
		}

		if (currentTime >= 4.5f)
		{
			bcanEat = true;
		}
	}
}

void ATomahowk::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	fireStraw = Cast<AFireStraw>(OtherActor);
	auto player = Cast<AVR_Player>(OtherActor);
	if (OtherActor == fireStraw)
	{
		if (bCanBake == true)
		{
			bisOverlab = true;
		}
	}

	if (bisWelldone == true)
	{
		if (bcanEat == true)
		{
			if (player)
			{
				if (OtherComp == player->mouthComp)
				{
					if (bisEat == false)
					{
						bisBone = true;
						UGameplayStatics::PlaySound2D(GetWorld(), sound);
						bisEat = true;

						meshComp1->SetHiddenInGame(true);
						meatOutline->SetHiddenInGame(true);
						meshComp4->SetHiddenInGame(false);
					}
				}
			}
		}
	}
}

