// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEvent.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"
#include <Components/WidgetComponent.h>
#include "Watch.h"

// Sets default values
AFireEvent::AFireEvent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	planeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component"));
	SetRootComponent(planeComp);

	skelComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skel Component"));
	skelComp->SetupAttachment(planeComp);
}

// Called when the game starts or when spawned
void AFireEvent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	watch = Cast<AWatch>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch::StaticClass()));
}

// Called every frame
void AFireEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector me = skelComp->GetComponentLocation();
	FVector target = watch->GetActorLocation();
	FVector dir = target - me;
	dir.Normalize();

	float speed = 100.0f;

	FVector p = me + dir * speed * DeltaTime;

	SetActorLocation(p);

	FVector startScale = GetActorScale3D();
	FVector endScale = FVector(0.01f, 0.01f, 0.01f);

	FVector setScale = FMath::Lerp(startScale, endScale, DeltaTime );
	SetActorScale3D(setScale);
}

