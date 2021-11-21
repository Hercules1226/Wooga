// Fill out your copyright notice in the Description page of Project Settings.


#include "LastHouse.h"
#include "VR_Player.h"
#include "GrabActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Stick.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ALastHouse::ALastHouse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(sceneComponent);

	tree1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree1"));
	tree1->SetupAttachment(sceneComponent);

	tree2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree2"));
	tree2->SetupAttachment(sceneComponent);

	tree3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree3"));
	tree3->SetupAttachment(sceneComponent);

	tree4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tree4"));
	tree4->SetupAttachment(sceneComponent);

	offMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Off Material"));

	onMaterial = CreateDefaultSubobject<UMaterial>(TEXT("On Material"));
}

// Called when the game starts or when spawned
void ALastHouse::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));


	tree1->OnComponentBeginOverlap.AddDynamic(this, &ALastHouse::OnCollisionEnter);
	tree2->OnComponentBeginOverlap.AddDynamic(this, &ALastHouse::OnCollisionEnter);
	tree3->OnComponentBeginOverlap.AddDynamic(this, &ALastHouse::OnCollisionEnter);
	tree4->OnComponentBeginOverlap.AddDynamic(this, &ALastHouse::OnCollisionEnter);

	tree1->SetMaterial(0, offMaterial);
}

// Called every frame
void ALastHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALastHouse::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	stick = Cast<AStick>(OtherActor);

	if (OtherActor == stick)
	{
		if (player->grabComp->bisStickR == true)
		{
			player->grabComp->RightReleaseAction();

			stick->SetActorLocationAndRotation(tree1->GetComponentLocation(), tree1->GetComponentRotation());

			tree1->SetMaterial(0, onMaterial);

			stick->SetActorHiddenInGame(true);
		}

		if (player->grabComp->bisStickL == true)
		{
			player->grabComp->LeftReleaseAction();

			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			stick->AttachToComponent(tree1, attachRules);

			tree1->SetMaterial(0, onMaterial);
			stick->SetActorHiddenInGame(true);
		}
	}
}

