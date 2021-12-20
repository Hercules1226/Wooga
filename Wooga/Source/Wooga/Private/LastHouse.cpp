// Fill out your copyright notice in the Description page of Project Settings.


#include "LastHouse.h"
#include "VR_Player.h"
#include "GrabActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Stick.h"
#include "Camera/CameraComponent.h"
#include <Kismet/GameplayStatics.h>
#include "MoveActorComponent.h"


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

	base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	base->SetupAttachment(sceneComponent);

	for (int i = 0; i < stickCount; i++)
	{
		FString stickName = "stick" + FString::FromInt(i + 1);
		stickArray.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName(*stickName)));
		stickArray[i]->SetupAttachment(sceneComponent);
	}

	complete = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Complete"));
	complete->SetupAttachment(sceneComponent);

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
}

// Called every frame
void ALastHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += DeltaTime;
	if (bisfinish == true)
	{
		FTimerHandle createTimer;
		GetWorld()->GetTimerManager().SetTimer(createTimer, this, &ALastHouse::CreateStick, 3.0f, false);
	}
	if (creatCount >= 15)
	{
		currentTime2 += DeltaTime;

		if (currentTime2 <= 4.f)
		{
			if (lastSoundEnd == false)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), createHouse);
				lastSoundEnd = true;
			}
			disTime += GetWorld()->DeltaTimeSeconds;
			blend = FMath::Lerp(1.f, 0.5f, disTime * 0.5f);
			complete->SetScalarParameterValueOnMaterials(TEXT("Length"), blend);
		}
		if (currentTime2 >= 10.f)
		{
			bisClear = true;
		}

	}

	if (isPlayerSet == true)
	{
		playerSetTime += DeltaTime;
		if (playerSetTime >= 2.5f)
		{
			player->SetActorLocationAndRotation(FVector(6864.32373f, 6981.561035f, 1318.585693f), FRotator(0.0f, -16, 0.f));
			isPlayerSet = false;
			player->moveComp->bisMove = false;

			// 43.888271f
		}
	}

	if (bisAttachStart == true)
	{
		tree1->SetMaterial(0, offMaterial);
		bisAttachStart = false;
	}
}


void ALastHouse::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	stick = Cast<AStick>(OtherActor);

	// 1
	if (check1 == true)
	{
		if (OverlappedComp == tree1 && OtherActor == stick)
		{
			if (player->grabComp->bisStickR == true)
			{
				stick->SetActorLocationAndRotation(tree1->GetComponentLocation(), tree1->GetComponentRotation());

				tree1->SetMaterial(0, onMaterial);
				tree2->SetMaterial(0, offMaterial);

				stick->SetActorHiddenInGame(true);

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				check2 = true;
				check1 = false;

				stick->Destroy();
			}

			if (player->grabComp->bisStickL == true)
			{
				stick->SetActorLocationAndRotation(tree1->GetComponentLocation(), tree1->GetComponentRotation());

				tree1->SetMaterial(0, onMaterial);
				tree2->SetMaterial(0, offMaterial);
				stick->SetActorHiddenInGame(true);

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				check2 = true;
				check1 = false;

				stick->Destroy();
			}
		}
	}

	// 2
	if (check2 == true)
	{
		if (OverlappedComp == tree2 && OtherActor == stick)
		{
			if (player->grabComp->bisStickR == true)
			{
				stick->SetActorLocationAndRotation(tree2->GetComponentLocation(), tree2->GetComponentRotation());

				tree2->SetMaterial(0, onMaterial);
				tree3->SetMaterial(0, offMaterial);

				stick->SetActorHiddenInGame(true);

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				check3 = true;
				check2 = false;

				stick->Destroy();
			}

			if (player->grabComp->bisStickL == true)
			{
				stick->SetActorLocationAndRotation(tree2->GetComponentLocation(), tree2->GetComponentRotation());

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				tree2->SetMaterial(0, onMaterial);
				tree3->SetMaterial(0, offMaterial);
				stick->SetActorHiddenInGame(true);

				check3 = true;
				check2 = false;

				stick->Destroy();
			}
		}
	}

	// 3
	if (check3 == true)
	{
		if (OverlappedComp == tree3 && OtherActor == stick)
		{
			if (player->grabComp->bisStickR == true)
			{
				stick->SetActorLocationAndRotation(tree3->GetComponentLocation(), tree3->GetComponentRotation());

				tree3->SetMaterial(0, onMaterial);
				tree4->SetMaterial(0, offMaterial);

				stick->SetActorHiddenInGame(true);

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				check4 = true;
				check3 = false;

				stick->Destroy();
			}

			if (player->grabComp->bisStickL == true)
			{
				stick->SetActorLocationAndRotation(tree3->GetComponentLocation(), tree3->GetComponentRotation());

				tree3->SetMaterial(0, onMaterial);
				tree4->SetMaterial(0, offMaterial);
				stick->SetActorHiddenInGame(true);

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				check4 = true;
				check3 = false;

				stick->Destroy();
			}
		}
	}

	// 4
	if (check4 == true)
	{
		if (OverlappedComp == tree4 && OtherActor == stick)
		{
			if (player->grabComp->bisStickR == true)
			{
				stick->SetActorLocationAndRotation(tree4->GetComponentLocation(), tree4->GetComponentRotation());

				tree4->SetMaterial(0, onMaterial);

				stick->SetActorHiddenInGame(true);

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

				bisfinish = true;
				check4 = false;
				isUIDown = true;

				stick->Destroy();
			}

			if (player->grabComp->bisStickL == true)
			{
				stick->SetActorLocationAndRotation(tree4->GetComponentLocation(), tree4->GetComponentRotation());

				tree4->SetMaterial(0, onMaterial);
				stick->SetActorHiddenInGame(true);
				currentTime = 0.f;

				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);

				bisfinish = true;
				check4 = false;
				isUIDown = true;

				stick->Destroy();
			}
			auto cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
			if (cameraManager)
			{
				cameraManager->StartCameraFade(0.f, 1.f, 2.5f, FLinearColor::Black, true, true);
				isPlayerSet = true;
			}
		}
	}
}

void ALastHouse::CreateStick()
{
	auto CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	if (CameraManager)
	{
		if (bisFadeStart == false)
		{
			CameraManager->StartCameraFade(1.f, 0.f, 2.5f, FLinearColor::Black, true, true);
			bisFadeStart = true;
		}
	}

	if (creatCount < 21)
	{
		if (currentTime > 0.2f)
		{
			if (creatCount < 16)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), overlabSound);
			}
			base->SetHiddenInGame(true);
			stickArray[creatCount]->SetHiddenInGame(false);
			creatCount++;
			currentTime = 0;
		}
	}
	if (creatCount == 20)
	{
		bisfinish = false;
	}


}

