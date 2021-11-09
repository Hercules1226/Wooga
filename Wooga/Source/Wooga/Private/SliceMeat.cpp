// Fill out your copyright notice in the Description page of Project Settings.


#include "SliceMeat.h"
#include "Cutting2.h"
#include "Materials/MaterialInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASliceMeat::ASliceMeat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	front = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front"));
	front->SetupAttachment(rootComp);

	back = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back"));
	back->SetupAttachment(rootComp);

	onMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("On Material"));

}

// Called when the game starts or when spawned
void ASliceMeat::BeginPlay()
{
	Super::BeginPlay();
	
	cutting2 = Cast<ACutting2>(UGameplayStatics::GetActorOfClass(GetWorld(), ACutting2::StaticClass()));

	frontPos = front->GetRelativeLocation();
	targetFrontPos = front->GetRelativeLocation() + FVector(0.f, -20.f, 0.f) * 3.f;

	backPos = back->GetRelativeLocation();
	targetBackPos = back->GetRelativeLocation() + FVector(0.f, 20.f, 0.f) * 3.f;

	frontRot = front->GetRelativeRotation();
	targetFrontRot = front->GetRelativeRotation() + FRotator(-1.f, 0.f, 0.f) * 3.f;

	backRot = back->GetRelativeRotation();
	targetBackRot = back->GetRelativeRotation() + FRotator(-2.f, 0.f, 0.f) * 3.f;
}

// Called every frame
void ASliceMeat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cutting2)
	{
		if (cutting2->bisfinish == true)
		{
			frontPos = FMath::Lerp(frontPos, targetFrontPos, GetWorld()->DeltaTimeSeconds * 2);
			backPos = FMath::Lerp(backPos, targetBackPos, GetWorld()->DeltaTimeSeconds * 2);

			/*topRot = FMath::Lerp(topRot, targetTopRot, GetWorld()->DeltaTimeSeconds * 2);
			bottomRot = FMath::Lerp(bottomRot, targetBottomRot, GetWorld()->DeltaTimeSeconds * 2);*/

			front->SetRelativeLocation(frontPos);
			//front->SetRelativeRotation(frontPos);
			back->SetRelativeLocation(backPos);
			//back->SetRelativeRotation(backPos);
			front->SetMaterial(0, onMaterial);
			back->SetMaterial(0, onMaterial);


			disTime += GetWorld()->DeltaTimeSeconds;
			blend = FMath::Lerp(0.f, 1.f, disTime * 0.5f);

			front->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);
			back->SetScalarParameterValueOnMaterials(TEXT("Amount"), blend);
		}
	}
}

