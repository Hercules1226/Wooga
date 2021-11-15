// Fill out your copyright notice in the Description page of Project Settings.


#include "Tomahowk.h"
#include "FireStraw.h"

// Sets default values
ATomahowk::ATomahowk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);

	medium = CreateDefaultSubobject<UMaterialInstance>(TEXT("Medium"));
	welldone = CreateDefaultSubobject<UMaterialInstance>(TEXT("Welldone"));
}

// Called when the game starts or when spawned
void ATomahowk::BeginPlay()
{
	Super::BeginPlay();
	meshComp->OnComponentBeginOverlap.AddDynamic(this, &ATomahowk::OnCollisionEnter);
}

// Called every frame
void ATomahowk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (bisOverlab == true)
	{
	if (currentTime >= 2.f)
	{
		meshComp->SetMaterial(0, medium);
	}

	if (currentTime >= 4.f)
	{
		meshComp->SetMaterial(0, welldone);
	}
	}
}

void ATomahowk::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	fireStraw = Cast<AFireStraw>(OtherActor);

	if (OtherActor == fireStraw)
	{
		bisOverlab = true;
		currentTime = 0;
	}
}

