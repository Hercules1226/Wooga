// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_InformUIPannel.h"
#include <Components/WidgetComponent.h>
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "VR_Player.h"
#include "SJ_WoogaGameModeBase.h"
#include "SJ_InformUICreate.h"
#include "Particles/ParticleSystemComponent.h"
#include "SJ_Actor_TitleUI.h"


// Sets default values
ASJ_InformUIPannel::ASJ_InformUIPannel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);

	informUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("InformUI"));
	informUI->SetupAttachment(rootComp);

	range = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	range->SetupAttachment(rootComp);

	informMark = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InformMark"));
	informMark->SetupAttachment(rootComp);

	informFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("InformFX"));
	informFX->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_InformUIPannel::BeginPlay()
{
	Super::BeginPlay();

	// ���Ӹ�� ĳ��
	gameModeBase = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gameModeBase->flowState == EFlowState::InformWatch || gameModeBase->flowState == EFlowState::GoToCollectCourse)
	{
		FVector p1 = FVector(9897.0f, 10207.0f, 1260.0);

		SetActorLocation(p1);

		FRotator r1 = FRotator(0,58,0);

		SetActorRotation(r1);
	}
	
	range->OnComponentBeginOverlap.AddDynamic(this, &ASJ_InformUIPannel::RangeIn);
}

// Called every frame
void ASJ_InformUIPannel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �÷��̾ ������ ������UI �� ������ ���
	if (isTrigger == true)
	{
		RunningTime += DeltaTime;	

		if (RunningTime <= 1.0f)
		{

			FRotator changeRot = FRotator(FMath::Lerp(startRot.X, endRot.X, RunningTime), FMath::Lerp(startRot.Y, endRot.Y, RunningTime), FMath::Lerp(startRot.Z, endRot.Z, RunningTime));

			informMark->SetRelativeRotation(changeRot);

			//startPos = GetActorLocation();
			//endPos = GetActorLocation() + GetActorUpVector() * 100;
			FVector changePos = FMath::Lerp(startPos, endPos, RunningTime);

			informMark->SetRelativeLocation(changePos);

		}
	}
}

void ASJ_InformUIPannel::RangeIn(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AVR_Player>(OtherActor);

	if (player)
	{
		isTrigger = true;

		informFX->SetHiddenInGame(true);

		/*if (gameModeBase->flowState == EFlowState::GoToCollectCourse)
		{
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			titleUI = GetWorld()->SpawnActor<class ASJ_Actor_TitleUI>(bpCollectTitleUI, Param);

			UE_LOG(LogTemp, Warning, TEXT("ColletctTitle"));

			gameModeBase->SetState(EFlowState::CollectTitle);
		}*/
	}
}

