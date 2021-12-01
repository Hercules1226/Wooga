// Fill out your copyright notice in the Description page of Project Settings.


#include "String_nia.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Cable.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AString_nia::AString_nia()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	nia = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia"));

}

// Called when the game starts or when spawned
void AString_nia::BeginPlay()
{
	Super::BeginPlay();
	
	cable = Cast<ACable>(UGameplayStatics::GetActorOfClass(GetWorld(), ACable::StaticClass()));
}

// Called every frame
void AString_nia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cable->bIsTie == true)
	{
		nia->SetActive(true);
	}

	if (cable->niaStart == false)
	{
		nia->SetActive(false);
	}
}

