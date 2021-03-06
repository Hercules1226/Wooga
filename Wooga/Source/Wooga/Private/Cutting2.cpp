// Fill out your copyright notice in the Description page of Project Settings.


#include "Cutting2.h"
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
ACutting2::ACutting2()
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
void ACutting2::BeginPlay()
{
	Super::BeginPlay();

	handle->OnComponentBeginOverlap.AddDynamic(this, &ACutting2::OnCollisionEnter);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	fA = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));
	cutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));

	handleY = handle->GetRelativeLocation().Y;
	handleX = handle->GetRelativeLocation().X;

	/*handle->SetMaterial(0, offMaterial);
	handle->SetMaterial(1, offMaterial);*/
}

// Called every frame
void ACutting2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (bisOverlabR == true)
	{
		handleZ = player->rightHand->GetComponentLocation().Z;

		handle->SetRelativeLocation(FVector(handleX, handleY, handleZ));
	}*/

	if (bisOverlabL == true)
	{
		handleX = player->leftHand->GetComponentLocation().X;

		handle->SetRelativeLocation(FVector(handleX, handleY, handleZ));
	}

	if (cutting->bisfinish == true)
	{
		handle->SetHiddenInGame(false);
		line->SetHiddenInGame(true);
	}

	if (bisSound == true)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), cuttingSound);
		bisSound = false;
	}
}

void ACutting2::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//if (OtherActor == fA)
	//{
	//	bisOverlabR = true;

	//	player->rightHand->SetHiddenInGame(false);
	//	fA->SetActorHiddenInGame(false);

	//	handle->SetMaterial(0, onMaterialHand);
	//	handle->SetMaterial(1, onMaterialFA);
	//}



	//if (player->grabComp->bisGrabFistAxeL)
	//{
		if (OtherActor == fA)
		{
			bisOverlabL = true;
			handle->SetRelativeScale3D(FVector(1.2f, -1.2f, 1.2f));
			//player->leftHand->SetHiddenInGame(true);
			//fA->SetActorHiddenInGame(true);

			handle->SetMaterial(0, onMaterialHand);
			handle->SetMaterial(1, onMaterialFA);
		}
	//}


	//if (bisOverlabR == true)
	//{
	//	auto detachRock = Cast<ADetachRock>(OtherActor);
	//	if (OtherActor == detachRock)
	//	{
	//		player->rightHand->SetHiddenInGame(false);
	//		//?!
	//		fA->SetActorHiddenInGame(false);
	//		bisfinish = true;
	//		//UGameplayStatics::PlaySound2D(GetWorld(), cuttingSound);
	//		//fA->Destroy();
	//		SetActorHiddenInGame(true);
	//		//Destroy();
	//	}
	//}

	if (bisOverlabL == true)
	{
		auto detachRock = Cast<ADetachRock>(OtherActor);
		if (OtherActor == detachRock)
		{
			//player->leftHand->SetHiddenInGame(false);
			//fA->SetActorHiddenInGame(false);
			bisfinish = true;
			//UGameplayStatics::PlaySound2D(GetWorld(), cuttingSound);
			//fA->Destroy();
			//SetActorHiddenInGame(true);
			bisSound = true;
			//Destroy();
		}
	}

}

