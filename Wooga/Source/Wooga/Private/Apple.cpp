// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include "VR_Player.h"
#include "GrabActorComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"



// Sets default values
AApple::AApple()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	//
	// 물리 관련 설정
	boxComp->SetSimulatePhysics(false);
	boxComp->SetEnableGravity(false);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);

	mesh2 = CreateDefaultSubobject<UStaticMesh>(TEXT("Mesh2"));


	outLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Outline"));
	outLine->SetupAttachment(meshComp);
	outLine->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();

	FVector explosionLoc = GetActorLocation();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), explosion, explosionLoc);

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AApple::OnCollisionEnter);

	outLine->SetVisibility(false);

	meshComp->SetRenderCustomDepth(true);
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
}

void AApple::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<AVR_Player>(OtherActor);

	if (currentTime >= 1.f)
	{
		if (player)
		{
			if (player->grabComp->bisGrabApple == true)
			{
				if (OtherComp == player->mouthComp)
				{
					if (bisEat == false)
					{
						// Sound

						location = this->GetActorLocation();
						rotation = this->GetActorRotation();

						UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

						/*player->grabComp->LeftReleaseAction();
						player->grabComp->RightReleaseAction();
						this->Destroy();*/

						meshComp->SetStaticMesh(mesh2);
						currentTime = 0.f;
						bisEat = true;
					}

					else if (bisEat == true)
					{
						location = this->GetActorLocation();
						rotation = this->GetActorRotation();

						UAudioComponent* MySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundBase2, location, rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);

						player->grabComp->LeftReleaseAction();
						player->grabComp->RightReleaseAction();

						// 사과를 완전히 다 먹었는지 확인하는 변수
						bisEatComplete = true;
						this->Destroy();
					}
				}
			}
		}
	}
}

