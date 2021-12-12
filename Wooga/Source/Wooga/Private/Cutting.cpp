// Fill out your copyright notice in the Description page of Project Settings.


#include "Cutting.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GrabActorComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "VR_Player.h"
#include "FistAxe.h"
#include "Watch1.h"
#include "Watch2.h"
#include "Watch3.h"
#include "Watch4.h"
#include "Watch5.h"
#include "Watch6.h"
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
	watch1 = Cast<AWatch1>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch1::StaticClass()));
	watch2 = Cast<AWatch2>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch2::StaticClass()));
	watch3 = Cast<AWatch3>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch3::StaticClass()));
	watch4 = Cast<AWatch4>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch4::StaticClass()));
	watch5 = Cast<AWatch5>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch5::StaticClass()));
	watch6 = Cast<AWatch6>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch6::StaticClass()));


	handleX = handle->GetRelativeLocation().X;
	handleZ = handle->GetRelativeLocation().Z;
	/*handle->SetMaterial(0, offMaterial);*/
	handle->SetMaterial(1, offMaterial);
}

// Called every frame
void ACutting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bisOverlabR == true)
	{
		handleY = player->rightHand->GetComponentLocation().Y;

		handle->SetRelativeLocation(FVector(handleX, handleY, handleZ));
	}

	if (bisOverlabL == true)
	{
		handleY = player->leftHand->GetComponentLocation().Y;

		handle->SetRelativeLocation(FVector(handleX, handleY, handleZ));
	}
}

void ACutting::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (player->grabComp->bisGrabFistAxeL)
	{
		if (OtherActor == fA)
		{
			bisOverlabL = true;
			handle->SetRelativeScale3D(FVector(1.2f, -1.2f, 1.2f));
			player->leftHand->SetHiddenInGame(true);
			fA->SetActorHiddenInGame(true);

			handle->SetMaterial(0, onMaterialHand);
			handle->SetMaterial(1, onMaterialFA);
		}
	}

	if (bisOverlabL == true)
	{
		auto detachRock = Cast<ADetachRock>(OtherActor);
		if (OtherActor == detachRock)
		{
			fA->SetActorHiddenInGame(true);
			watch1->SetActorHiddenInGame(false);
			watch2->SetActorHiddenInGame(false);
			watch3->SetActorHiddenInGame(false);
			watch4->SetActorHiddenInGame(false);
			watch5->SetActorHiddenInGame(false);
			watch6->SetActorHiddenInGame(false);

			player->grabComp->LeftFistReleaseAction();

			bisfinish = true;
			//UGameplayStatics::PlaySound2D(GetWorld(), cuttingSound);
			//fA->Destroy();
			SetActorHiddenInGame(true);
			player->leftHand->SetHiddenInGame(false);
			bisSound = true;
			//rootComp->SetActive(false);
		}
	}
	/*if (player->grabComp->bisGrabFistAxeR)
	{
		if (OtherActor == fA)
		{
			bisOverlabR = true;

			player->rightHand->SetHiddenInGame(true);
			fA->SetActorHiddenInGame(true);

			watch1->SetActorHiddenInGame(true);
			watch2->SetActorHiddenInGame(true);
			watch3->SetActorHiddenInGame(true);
			watch4->SetActorHiddenInGame(true);
			watch5->SetActorHiddenInGame(true);
			watch6->SetActorHiddenInGame(true);

			handle->SetMaterial(0, onMaterialHand);
			handle->SetMaterial(1, onMaterialFA);
		}
	}*/



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

}

