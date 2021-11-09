// Fill out your copyright notice in the Description page of Project Settings.


#include "Cutting.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "VR_Player.h"
#include "FistAxe.h"
#include "DetachRock.h"
#include "GrabActorComponent.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ACutting::ACutting()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	handle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle"));
	handle->SetupAttachment(rootComp);

	line = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Line"));
	line->SetupAttachment(rootComp);

	constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint"));
	constraint->SetupAttachment(rootComp);

	onMaterialHand = CreateDefaultSubobject<UMaterialInstance>(TEXT("On MaterialHand"));
	onMaterialFA = CreateDefaultSubobject<UMaterialInstance>(TEXT("On MaterialFA"));

	offMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("On Material"));
}

// Called when the game starts or when spawned
void ACutting::BeginPlay()
{
	Super::BeginPlay();

	handle->OnComponentBeginOverlap.AddDynamic(this, &ACutting::OnCollisionEnter);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	fA = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));

	handleX = handle->GetRelativeLocation().X;
	handleZ = handle->GetRelativeLocation().Z;

	/*handle->SetMaterial(0, offMaterial);*/
	handle->SetMaterial(1, offMaterial);
}

// Called every frame
void ACutting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bisOverlab == true)
	{
		handleY = player->rightHand->GetComponentLocation().Y;

		handle->SetRelativeLocation(FVector(handleX, handleY, handleZ));
	}
}

void ACutting::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == fA)
	{
		bisOverlab = true;

		player->rightHand->SetHiddenInGame(true);
		fA->SetActorHiddenInGame(true);

		handle->SetMaterial(0, onMaterialHand);
		handle->SetMaterial(1, onMaterialFA);
	}

	if (bisOverlab == true)
	{
		auto detachRock = Cast<ADetachRock>(OtherActor);
		if (OtherActor == detachRock)
		{
			player->rightHand->SetHiddenInGame(false);
			fA->SetActorHiddenInGame(false);
			bisfinish = true;
			//fA->Destroy();
			SetActorHiddenInGame(true);
		}
	}

}

