// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_BoarLeapFXRange.h"
#include <Components/BoxComponent.h>
#include "SJ_Character_Boar.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASJ_Actor_BoarLeapFXRange::ASJ_Actor_BoarLeapFXRange()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	range = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	range->SetupAttachment(rootComp);
}

// Called when the game starts or when spawned
void ASJ_Actor_BoarLeapFXRange::BeginPlay()
{
	Super::BeginPlay();


	range->OnComponentEndOverlap.AddDynamic(this, &ASJ_Actor_BoarLeapFXRange::EndOverlap);
}

// Called every frame
void ASJ_Actor_BoarLeapFXRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASJ_Actor_BoarLeapFXRange::EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexs)
{
	boar = Cast<ASJ_Character_Boar>(OtherActor);

	if (OtherActor == boar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Leap"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Fireeeeeeeeeeeeeeee!!")));
		// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), leapParticle, boar->GetActorLocation(), GetActorRotation(), FVector(2, 2, 2));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), leapParticle, GetActorLocation(), GetActorRotation(), FVector(1, 1, 1));

		UGameplayStatics::PlaySound2D(GetWorld(), leapSound);
	}
}

