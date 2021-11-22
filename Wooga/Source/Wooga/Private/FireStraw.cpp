// Fill out your copyright notice in the Description page of Project Settings.


#include "FireStraw.h"
#include "VR_Player.h"
#include "FirePosition.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
#include "SJ_WoogaGameModeBase.h"

// Sets default values
AFireStraw::AFireStraw()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComp->SetupAttachment(RootComponent);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(boxComp);

	attenuationSettings = CreateDefaultSubobject<USoundAttenuation>(TEXT("AttenuationSettings"));

	pointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	pointLight->SetupAttachment(boxComp);

	outLine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutLine"));
	outLine->SetupAttachment(meshComp);
	fireLoopSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FireLoopSound"));
}

// Called when the game starts or when spawned
void AFireStraw::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameMode->flowState == EFlowState::CuttingPig || gameMode->flowState == EFlowState::GoToFireUse)
	{
		FVector p = FVector(5173, 8000, 1177);

		SetActorLocation(p);

		FVector s = FVector(0.4f, 0.4f, 0.4f);

		SetActorRelativeScale3D(s);
	}



	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AFireStraw::OnCollisionEnter);

	outLine->SetVisibility(false);

	//fireLoopSound->Stop();
	isClear = false;
}

// Called every frame
void AFireStraw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bisOverlab == true)
	{
		smogCurrentTime += GetWorld()->DeltaTimeSeconds;
		fireCurrentTime += GetWorld()->DeltaTimeSeconds;

		if (bisSmog == false)
		{
			if (smogCurrentTime >= 5.f)
			{
				// Sound

				location = this->GetActorLocation();
				rotation = this->GetActorRotation();
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBase2, location);
				//UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBase3, location);

				//fireLoopSound->Play();
				pointLight->SetHiddenInGame(false);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireFactory, GetActorLocation() + FVector(0.f, 0.0f, 0.f));
				bisSmog = true;
				isClear = true;
			}
		}
	}

}

void AFireStraw::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto firePosition = Cast<AFirePosition>(OtherActor);
	auto player = Cast<AVR_Player>(OtherActor);

	if (firePosition)
	{
		if (firePosition->bisFire == true)
		{
			location = this->GetActorLocation();
			rotation = this->GetActorRotation();

			fireLoopSound->Play();

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), smogFactory, GetActorLocation() + FVector(0.f, 0.0f, 0.f));
			bisReadyFire = true;
			firePosition->Destroy();
		}
	}
	if (bisReadyFire == true)
	{
		if (player)
		{
			if (player->mouthComp)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Fireeeeeeeeeeeeeeee!!")));
				bisOverlab = true;
			}
		}
	}
	else
	{
		return;
	}
}

