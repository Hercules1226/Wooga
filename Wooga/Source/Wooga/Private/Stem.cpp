// Fill out your copyright notice in the Description page of Project Settings.

#include "Stem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Apple.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include <Components/SphereComponent.h>

// Sets default values
AStem::AStem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Component"));
	SetRootComponent(boxComp);
	boxComp->SetSimulatePhysics(false);
	boxComp->SetEnableGravity(false);

	topLoc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopLoc"));
	topLoc->SetupAttachment(boxComp);

	top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	top->SetupAttachment(topLoc);
	top->SetSimulatePhysics(false);
	top->SetEnableGravity(false);

	midLoc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MidLoc"));
	midLoc->SetupAttachment(boxComp);

	mid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mid"));
	mid->SetupAttachment(midLoc);
	mid->SetSimulatePhysics(false);
	mid->SetEnableGravity(false);

	bottomLoc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomLoc"));
	bottomLoc->SetupAttachment(boxComp);

	bottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom"));
	bottom->SetupAttachment(bottomLoc);
	bottom->SetSimulatePhysics(false);
	bottom->SetEnableGravity(false);

	constraint1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint1"));
	constraint1->SetupAttachment(boxComp);

	constraint2 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint2"));
	constraint2->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void AStem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

