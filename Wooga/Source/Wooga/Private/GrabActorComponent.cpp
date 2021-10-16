// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabActorComponent.h"
#include "VR_Player.h"
#include "FireRock.h"
#include "DrawDebugHelpers.h"
#include "HandActorComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UGrabActorComponent::UGrabActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Player Casting
	player = Cast<AVR_Player>(GetOwner());

	//fireRock = Cast<AFireRock>(fireRock);
}


// Called every frame
void UGrabActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGrabActorComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("RightGrip", IE_Pressed, this, &UGrabActorComponent::RightGrabAction);
	PlayerInputComponent->BindAction("RightGrip", IE_Released, this, &UGrabActorComponent::RightReleaseAction);
	PlayerInputComponent->BindAction("LeftGrip", IE_Pressed, this, &UGrabActorComponent::LeftGrabAction);
	PlayerInputComponent->BindAction("LeftGrip", IE_Released, this, &UGrabActorComponent::LeftReleaseAction);
	//PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &UGrabActorComponent::Reload);

}

// �׷� ����
void UGrabActorComponent::ShowGrabLine()
{
	bIsShowing = true;
}

void UGrabActorComponent::HideGrabLine()
{
	bIsShowing = false;
	// ������ ����
	grabObject = FHitResult();
}

void UGrabActorComponent::RightDrawGrabLine()
{
	DrawDebugSphere(GetWorld(), player->rightHand->GetComponentLocation(), grabRange, 30, FColor::Green, false, -1, 0, 1);
	FHitResult hitInfo;
	FVector startPos = player->rightHand->GetComponentLocation();

	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(player);
	player->handComp->targetGripValueRight = 1.0f;

	if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(grabRange), queryParams))
	{
		grabObject = hitInfo;
	}
	else
	{
		grabObject = FHitResult();
	}

}

void UGrabActorComponent::LeftDrawGrabLine()
{
	DrawDebugSphere(GetWorld(), player->leftHand->GetComponentLocation(), grabRange, 30, FColor::Green, false, -1, 0, 1);
	FHitResult hitInfo;
	FVector startPos = player->leftHand->GetComponentLocation();

	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(player);
	player->handComp->targetGripValueLeft = 1.0f;

	if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(grabRange), queryParams))
	{
		grabObject = hitInfo;
	}
	else
	{
		grabObject = FHitResult();
	}
}

void UGrabActorComponent::RightGrabAction()
{
	bisRightGrab = true;
	RightDrawGrabLine();

	AActor* grabActor = grabObject.GetActor();

	if (grabActor == nullptr)
	{
		return;
	}

	RGripFireRock(grabActor);
}

void UGrabActorComponent::RightReleaseAction()
{
	if (bisRightGrab == true)
	{
		if (fireRockR)
		{
			fireRockR->boxComp->SetEnableGravity(true);
			// �� �ڸ����� ��������
			fireRockR->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			fireRockR->boxComp->SetSimulatePhysics(true);

			fireRockR = nullptr;
			bisRightGrab = false;
		}
	}
	// ������ �Ǵ� �ִϸ��̼�
	player->handComp->targetGripValueRight = 0.0f;

}

void UGrabActorComponent::LeftGrabAction()
{
	bisLeftGrab = true;
	LeftDrawGrabLine();

	AActor* grabActor = grabObject.GetActor();

	if (grabActor == nullptr)
	{
		return;
	}

	LGripFireRock(grabActor);
}

void UGrabActorComponent::LeftReleaseAction()
{
	if (bisLeftGrab == true)
	{
		if (fireRockL)
		{
			fireRockL->boxComp->SetEnableGravity(true);
			// �� �ڸ����� ��������
			fireRockL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			fireRockL->boxComp->SetSimulatePhysics(true);

			fireRockL = nullptr;
			bisLeftGrab = false;
		}
	}
	// ������ �Ǵ� �ִϸ��̼�
	player->handComp->targetGripValueLeft = 0.0f;
}

void UGrabActorComponent::RGripFireRock(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
		if (fr.Contains("GR"))
		{
			fireRockR = Cast<AFireRock>(grabActor);

			if (fireRockR)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
				//fireRock->SetActorHiddenInGame(false);
				//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
				FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

				// �տ� ���̱�
				fireRockR->boxComp->SetSimulatePhysics(false);

				fireRockR->AttachToComponent(player->rightHand, attachRules, TEXT("RGrabPoint"));
				// ������ ��� �ִϸ��̼�
				player->handComp->targetGripValueRight = 0.7f;

				// ������Ʈ�� ������� ��ġ ���
				fireRockR->boxComp->SetRelativeLocation((fireRockR->grabOffset));

				fireRockR->boxComp->SetEnableGravity(false);
			}
		}
	//}
}

void UGrabActorComponent::LGripFireRock(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
		if (fr.Contains("GR"))
		{
			fireRockL = Cast<AFireRock>(grabActor);

			if (fireRockL)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
				//fireRock->SetActorHiddenInGame(false);
				//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
				FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

				// �տ� ���̱�
				fireRockL->boxComp->SetSimulatePhysics(false);


				fireRockL->AttachToComponent(player->leftHand, attachRules, TEXT("LGrabPoint"));
				// �޼� ��� �ִϸ��̼�
				player->handComp->targetGripValueLeft = 0.7f;


				// ������Ʈ�� ������� ��ġ ���
				fireRockL->boxComp->SetRelativeLocation((fireRockL->grabOffset));

				fireRockL->boxComp->SetEnableGravity(false);
			}
		}
	//}
}

