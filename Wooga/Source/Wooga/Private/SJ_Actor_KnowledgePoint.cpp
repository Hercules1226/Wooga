// Fill out your copyright notice in the Description page of Project Settings.


#include "SJ_Actor_KnowledgePoint.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include "VR_Player.h"
#include "Watch1.h"
#include "Watch2.h"
#include "Watch3.h"
#include "Watch4.h"
#include "Watch5.h"
#include "Watch6.h"

// Sets default values
ASJ_Actor_KnowledgePoint::ASJ_Actor_KnowledgePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);

	skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	skeletalMesh->SetupAttachment(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void ASJ_Actor_KnowledgePoint::BeginPlay()
{
	Super::BeginPlay();

	meshComp->OnComponentBeginOverlap.AddDynamic(this, &ASJ_Actor_KnowledgePoint::OnOverlap);

}

// Called every frame
void ASJ_Actor_KnowledgePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector startScale = GetActorScale3D();
	FVector endScale = FVector(0.01f, 0.02f, 0.02f);

	FVector setScale = FMath::Lerp(startScale, endScale, DeltaTime * 1.5f);
	SetActorScale3D(setScale);

	player = Cast<AVR_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AVR_Player::StaticClass()));

	me = GetActorLocation();

	// ���� �߰�
	if (player->knowledgePoint == 0)
	{
		watch1 = Cast<AWatch1>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch1::StaticClass()));

		target = watch1->GetActorLocation();

		dir = target - me;
		dir.Normalize();

		p = me + dir * speed * DeltaTime;

		SetActorLocation(p);
	}
	// ä��
	if (player->knowledgePoint == 1)
	{
		watch2 = Cast<AWatch2>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch2::StaticClass()));

		target = watch2->GetActorLocation();

		dir = target - me;
		dir.Normalize();

		p = me + dir * speed * DeltaTime;

		SetActorLocation(p);
	}
	// �ָԵ���
	if (player->knowledgePoint == 2)
	{
		watch3 = Cast<AWatch3>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch3::StaticClass()));

		target = watch3->GetActorLocation();

		dir = target - me;
		dir.Normalize();

		p = me + dir * speed * DeltaTime;

		SetActorLocation(p);
	}
	// ���� �߰�
	if (player->knowledgePoint == 3)
	{	
		watch4 = Cast<AWatch4>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch4::StaticClass()));

		target = watch4->GetActorLocation();

		dir = target - me;
		dir.Normalize();

		p = me + dir * speed * DeltaTime;

		SetActorLocation(p);
	}
	// �������
	if (player->knowledgePoint == 4)
	{
		watch5 = Cast<AWatch5>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch5::StaticClass()));

		target = watch5->GetActorLocation();

		dir = target - me;
		dir.Normalize();

		p = me + dir * speed * DeltaTime;

		SetActorLocation(p);
	}
	// ����
	if (player->knowledgePoint == 5)
	{
		watch6 = Cast<AWatch6>(UGameplayStatics::GetActorOfClass(GetWorld(), AWatch6::StaticClass()));

		target = watch6->GetActorLocation();

		dir = target - me;
		dir.Normalize();

		p = me + dir * speed * DeltaTime;

		SetActorLocation(p);
	}
}

void ASJ_Actor_KnowledgePoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	watch1 = Cast<AWatch1>(OtherActor);
	watch2 = Cast<AWatch2>(OtherActor);
	watch3 = Cast<AWatch3>(OtherActor);
	watch4 = Cast<AWatch4>(OtherActor);
	watch5 = Cast<AWatch5>(OtherActor);
	watch6 = Cast<AWatch6>(OtherActor);
	

	// ���� Ȱ�� ���� ����Ʈ
	if (OtherActor == watch1 && player->knowledgePoint == 0)
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		// ��ġ�� ��¦�� �� �ֵ��� �ϴ� ����
		watch1->isBlink = true;

		Destroy();
		player->knowledgePoint = 1;
	}
	// ä�� ���� ����Ʈ
	else if (OtherActor == watch2 && player->knowledgePoint == 1)
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		// ��ġ�� ��¦�� �� �ֵ��� �ϴ� ����
		watch2->isBlink = true;

		Destroy();
		player->knowledgePoint = 2;
	}
	// �ָԵ��� ��������Ʈ
	else if (OtherActor == watch3 && player->knowledgePoint == 2)
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		// ��ġ�� ��¦�� �� �ֵ��� �ϴ� ����
		watch3->isBlink = true;

		Destroy();
		player->knowledgePoint = 3;
	}
	// ���� Ȱ�� ��������Ʈ
	else if (OtherActor == watch4 && player->knowledgePoint == 3)
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		// ��ġ�� ��¦�� �� �ֵ��� �ϴ� ����
		watch4->isBlink = true;

		Destroy();
		player->knowledgePoint = 4;
	}
	// ������� ��������Ʈ
	else if (OtherActor == watch5 && player->knowledgePoint == 4)
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		// ��ġ�� ��¦�� �� �ֵ��� �ϴ� ����
		watch5->isBlink = true;

		Destroy();
		player->knowledgePoint = 5;
	}
	// ���� ��������Ʈ
	else if (OtherActor == watch5 && player->knowledgePoint == 4)
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);

		// ��ġ�� ��¦�� �� �ֵ��� �ϴ� ����
		watch6->isBlink = true;

		Destroy();
		player->knowledgePoint = 6;
	}
}


