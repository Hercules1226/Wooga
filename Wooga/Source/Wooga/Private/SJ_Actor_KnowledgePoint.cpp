// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_KnowledgePoint.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"
#include "Watch1.h"

// Sets default values
ASJ_Actor_KnowledgePoint::ASJ_Actor_KnowledgePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_KnowledgePoint::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	meshComp->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_KnowledgePoint::OnOverlap);

	watch1 = Cast<AWatch1>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch1::StaticClass()));
}

// Called every frame
void ASJ_Actor_KnowledgePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	me = GetActorLocation();

	if (player->knowledgePoint == 0)
	{
		target = watch1->GetActorLocation();

		dir = target - me;
		dir.Normalize();

		p = me + dir * speed * DeltaTime;

		SetActorLocation(p);
	}
}

void ASJ_Actor_KnowledgePoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	watch1 = Cast<AWatch1>(OtherActor);

	if (OtherActor == watch1 && player->knowledgePoint == 0)
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		Destroy();
		player->knowledgePoint = 1;
	}
}

