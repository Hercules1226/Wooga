// Fill out your copyright notice in the Description page of Project Settings.


#include "SlicePig.h"
#include "Cutting.h"
#include "Materials/MaterialInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ASlicePig::ASlicePig()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	pigHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pig Head"));
	pigHead->SetupAttachment(rootComp);

	top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	top->SetupAttachment(rootComp);

	bottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom"));
	bottom->SetupAttachment(rootComp);

	decal1 = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal1"));
	decal1->SetupAttachment(rootComp);

	decal2 = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal2"));
	decal2->SetupAttachment(rootComp);

	decal3 = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal3"));
	decal3->SetupAttachment(rootComp);

	decal4 = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal4"));
	decal4->SetupAttachment(rootComp);

	decal5 = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal5"));
	decal5->SetupAttachment(rootComp);

	decalCollision1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecalCollision1"));
	decalCollision1->SetupAttachment(rootComp);

	decalCollision2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecalCollision2"));
	decalCollision2->SetupAttachment(rootComp);

	decalCollision3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecalCollision3"));
	decalCollision3->SetupAttachment(rootComp);

	decalCollision4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecalCollision4"));
	decalCollision4->SetupAttachment(rootComp);

	decalCollision5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DecalCollision5"));
	decalCollision5->SetupAttachment(rootComp);

	onMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("On Material"));
	decalMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("DecalMaterial"));

}

// Called when the game starts or when spawned
void ASlicePig::BeginPlay()
{
	Super::BeginPlay();

	decalCollision1->OnComponentBeginOverlap.AddDynamic(this, &ASlicePig::OnCollisionEnter);
	decalCollision2->OnComponentBeginOverlap.AddDynamic(this, &ASlicePig::OnCollisionEnter);
	decalCollision3->OnComponentBeginOverlap.AddDynamic(this, &ASlicePig::OnCollisionEnter);
	decalCollision4->OnComponentBeginOverlap.AddDynamic(this, &ASlicePig::OnCollisionEnter);
	decalCollision5->OnComponentBeginOverlap.AddDynamic(this, &ASlicePig::OnCollisionEnter);


	cutting = Cast<ACutting>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting::StaticClass()));

	topPos = top->GetRelativeLocation();
	targetTopPos = top->GetRelativeLocation() + FVector(0.f, 0.f, 20.f) * 3.f;

	bottomPos = bottom->GetRelativeLocation();
	targetBottomPos = bottom->GetRelativeLocation() + FVector(0.f, 0.f, -20.f) * 3.f;

	topRot = top->GetRelativeRotation();
	targetTopRot = top->GetRelativeRotation() + FRotator(-1.f, 0.f, 0.f) * 3.f;

	bottomRot = bottom->GetRelativeRotation();
	targetBottomRot = bottom->GetRelativeRotation() + FRotator(-2.f, 0.f, 0.f) * 3.f;

}

// Called every frame
void ASlicePig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cutting)
	{
		if (cutting->bisfinish == true)
		{

			topPos = FMath::Lerp(topPos, targetTopPos, GetWorld()->DeltaTimeSeconds * 2);
			bottomPos = FMath::Lerp(bottomPos, targetBottomPos, GetWorld()->DeltaTimeSeconds * 2);

			/*topRot = FMath::Lerp(topRot, targetTopRot, GetWorld()->DeltaTimeSeconds * 2);
			bottomRot = FMath::Lerp(bottomRot, targetBottomRot, GetWorld()->DeltaTimeSeconds * 2);*/

			top->SetRelativeLocation(topPos);
			//top->SetRelativeRotation(topRot);
			bottom->SetRelativeLocation(bottomPos);
			//bottom->SetRelativeRotation(bottomRot);

			disTime += GetWorld()->DeltaTimeSeconds;
			blend = FMath::Lerp(0.f, 1.f, disTime * 2.f);

			pigHead->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);
			top->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);
			bottom->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);

			if (effectOn == 0)
			{
				effectOn = 1;
			}

		}
	}

	if (effectOn == 1)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleFactory, GetActorLocation() + FVector(0.f, 0.0f, 50.f));
		effectOn = 2;
	}
}

void ASlicePig::OnCollisionEnter(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp == cutting->handle && OverlappedComp == decalCollision1)
	{
		decal1->SetMaterial(0, decalMaterial);
		if (sound1 == true)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), sound);

			sound2 = true;
			sound1 = false;
		}
	}

	if (OtherComp == cutting->handle && OverlappedComp == decalCollision2)
	{
		decal2->SetMaterial(0, decalMaterial);
		if (sound2 == true)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), sound);

			sound3 = true;
			sound2 = false;
		}
	}

	if (OtherComp == cutting->handle && OverlappedComp == decalCollision3)
	{
		decal3->SetMaterial(0, decalMaterial);
		if (sound3 == true)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), sound);

			sound4 = true;
			sound3 = false;
		}
	}

	if (OtherComp == cutting->handle && OverlappedComp == decalCollision4)
	{
		decal4->SetMaterial(0, decalMaterial);
		if (sound4 == true)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), sound);

			sound5 = true;
			sound4 = false;
		}
	}

	if (OtherComp == cutting->handle && OverlappedComp == decalCollision5)
	{
		decal5->SetMaterial(0, decalMaterial);
		if (sound5 == true)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), sound);

			sound5 = false;
		}
	}
}
