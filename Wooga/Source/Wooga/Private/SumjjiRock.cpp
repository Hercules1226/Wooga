// Fill out your copyright notice in the Description page of Project Settings.


#include "SumjjiRock.h"
#include "Components/StaticMeshComponent.h"
#include "VR_Player.h"

// Sets default values
ASumjjiRock::ASumjjiRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sumjji = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sumjji"));
	SetRootComponent(sumjji);

	rock1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock1"));
	rock1->SetupAttachment(sumjji);

	rock2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock2"));
	rock2->SetupAttachment(sumjji);

	rock3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock3"));
	rock3->SetupAttachment(sumjji);

	rock4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock4"));
	rock4->SetupAttachment(sumjji);

	onMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("On Material"));

	offMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("off Material"));
}

// Called when the game starts or when spawned
void ASumjjiRock::BeginPlay()
{
	Super::BeginPlay();
	sumjji->OnComponentBeginOverlap.AddDynamic(this, &ASumjjiRock::OnCollisionEnter);
	rock1->OnComponentBeginOverlap.AddDynamic(this, &ASumjjiRock::OnCollisionEnter);
	rock2->OnComponentBeginOverlap.AddDynamic(this, &ASumjjiRock::OnCollisionEnter);
	rock3->OnComponentBeginOverlap.AddDynamic(this, &ASumjjiRock::OnCollisionEnter);
	rock4->OnComponentBeginOverlap.AddDynamic(this, &ASumjjiRock::OnCollisionEnter);
}

// Called every frame
void ASumjjiRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASumjjiRock::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (currentTime >= 1.f)
	//{
	//	detachRock = Cast<ADetachRock>(OtherActor);
	//	if (OtherActor == detachRock)
	//	{
	//		// Nuckback
	//		myPos = player->leftHand->GetRelativeLocation();
	//		knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
	//		myPos = knockbackPos;
	//		player->leftHand->SetRelativeLocation(myPos);
	//		rock2->SetMaterial(0, onMaterial);
	//		bisOverlab = true;

	//		childRock = Cast<AHalfRock>(halfRock->GetChildActor());
	//		childRock->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//		player->grabComp->RightReleaseAction();
	//		fakeHand->SetHiddenInGame(true);
	//		player->rightHand->SetHiddenInGame(false);
	//		handHologramR->SetHiddenInGame(true);
	//		bisD1 = true;

	//		halfRockComp = Cast<UStaticMeshComponent>(childRock->GetDefaultSubobjectByName(TEXT("halfRock")));
	//		halfRockComp->SetSimulatePhysics(true);
	//		halfRockComp->SetEnableGravity(true);
	//		currentTime = 0.f;
	//	}
}

