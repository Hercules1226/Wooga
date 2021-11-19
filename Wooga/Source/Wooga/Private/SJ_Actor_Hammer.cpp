// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_Hammer.h"
#include <Components/StaticMeshComponent.h>
#include "Kismet/GameplayStatics.h"
#include "SJ_Character_Boar.h"

// Sets default values
ASJ_Actor_Hammer::ASJ_Actor_Hammer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	hammer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hammer"));
	SetRootComponent(hammer);
}

// Called when the game starts or when spawned
void ASJ_Actor_Hammer::BeginPlay()
{
	Super::BeginPlay();
	
	boar = Cast<ASJ_Character_Boar>(UGameplayStatics::GetActorOfClass(GetWorld(), ASJ_Character_Boar::StaticClass()));

	FVector  b = boar->GetActorLocation();
	FVector  p = b + boar->GetActorRightVector() * 100;
}

// Called every frame
void ASJ_Actor_Hammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector  me = GetActorLocation();
	FVector  tar = boar->GetActorLocation();
	FVector  dir = tar - me;
	dir.Normalize();

	hammer->AddForce(dir * 1000);
}

