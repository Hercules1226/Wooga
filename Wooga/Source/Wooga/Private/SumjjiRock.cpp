// Fill out your copyright notice in the Description page of Project Settings.


#include "SumjjiRock.h"
#include "Components/StaticMeshComponent.h"
#include "VR_Player.h"
#include "Tomahowk.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASumjjiRock::ASumjjiRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	sumjji = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sumjji"));
	sumjji->SetupAttachment(rootComp);

	rock1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock1"));
	rock1->SetupAttachment(sumjji);

	rock2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock2"));
	rock2->SetupAttachment(sumjji);

	rock3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock3"));
	rock3->SetupAttachment(sumjji);

	rock4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rock4"));
	rock4->SetupAttachment(sumjji);

	outLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline"));
	outLine->SetupAttachment(sumjji);
	outLine->SetCollisionProfileName(TEXT("NoCollision"));

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

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));
	bone = Cast<ATomahowk>(UGameplayStatics::GetActorOfClass(GetWorld(), ATomahowk::StaticClass()));
	rock1->SetMaterial(0, onMaterial);

	outLine->SetVisibility(false);
}

// Called every frame
void ASumjjiRock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (bisOverlab == true)
	{
		myPos = FMath::Lerp(myPos, returnKnockbackPos, 5.f * GetWorld()->DeltaTimeSeconds);
		player->leftHand->SetRelativeLocation(myPos);
		// 물어보기
		if (FVector::Dist(myPos, returnKnockbackPos) < 1.f)
		{
			bisOverlab = false;
		}
	}
}

void ASumjjiRock::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bone->bisBone == true)
	{
		if (currentTime >= 1.f)
		{
			if (OverlappedComp == rock1 && OtherComp == bone->meshComp4)
			{
				// Nuckback
				myPos = player->leftHand->GetRelativeLocation();
				knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
				myPos = knockbackPos;
				player->leftHand->SetRelativeLocation(myPos);
				bisOverlab = true;

				UGameplayStatics::PlaySound2D(GetWorld(), Sound);

				rock1->SetSimulatePhysics(true);
				rock1->SetEnableGravity(true);

				rock1->SetMaterial(0, offMaterial);
				rock2->SetMaterial(0, onMaterial);

				rock1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				rock1->DetachFromParent(true);
				currentTime = 0.f;

				bisRock2 = true;
			}

			if (bisRock2 == true)
			{
				if (OverlappedComp == rock2 && OtherComp == bone->meshComp4)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					UGameplayStatics::PlaySound2D(GetWorld(), Sound);

					rock2->SetSimulatePhysics(true);
					rock2->SetEnableGravity(true);

					rock2->SetMaterial(0, offMaterial);
					rock3->SetMaterial(0, onMaterial);

					rock2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock2->DetachFromParent(true);
					currentTime = 0.f;

					bisRock3 = true;
				}
			}

			if (bisRock3 == true)
			{
				if (OverlappedComp == rock3 && OtherComp == bone->meshComp4)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					UGameplayStatics::PlaySound2D(GetWorld(), Sound);

					rock3->SetSimulatePhysics(true);
					rock3->SetEnableGravity(true);

					rock3->SetMaterial(0, offMaterial);
					rock4->SetMaterial(0, onMaterial);

					rock3->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock3->DetachFromParent(true);
					currentTime = 0.f;

					bisRock4 = true;
				}
			}

			if (bisRock4 == true)
			{
				if (OverlappedComp == rock4 && OtherComp == bone->meshComp4)
				{
					// Nuckback
					myPos = player->leftHand->GetRelativeLocation();
					knockbackPos = player->leftHand->GetRelativeLocation() + FVector(1.f, 0.f, 1.f) * -3.f;
					myPos = knockbackPos;
					player->leftHand->SetRelativeLocation(myPos);
					bisOverlab = true;

					UGameplayStatics::PlaySound2D(GetWorld(), Sound);

					rock4->SetSimulatePhysics(true);
					rock4->SetEnableGravity(true);

					rock4->SetMaterial(0, offMaterial);
					//rock5->SetMaterial(0, onMaterial);

					rock4->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					rock4->DetachFromParent(true);
					currentTime = 0.f;

					bisRockFin = true;
					bone->SetActorHiddenInGame(true);
					bone->boneOutline->SetHiddenInGame(true);
				}
			}
		}
	}
}

