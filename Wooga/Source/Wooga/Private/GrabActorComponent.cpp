// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabActorComponent.h"
#include "VR_Player.h"
#include "Apple.h"
#include "Stick.h"
#include "Stem.h"
#include "FireRock.h"
#include "FireRock2.h"
#include "FirePosition.h"
#include "FistAxe.h"
#include "HalfRock.h"
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


	stemR = Cast<AStem>(UGameplayStatics::GetActorOfClass(GetWorld(), AStem::StaticClass()));
	stemL = Cast<AStem>(UGameplayStatics::GetActorOfClass(GetWorld(), AStem::StaticClass()));
	fistAxe = Cast<AFistAxe>(UGameplayStatics::GetActorOfClass(GetWorld(), AFistAxe::StaticClass()));


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
	RGripFireRock2(grabActor);
	RGripFirePosition(grabActor);
	RGripApple(grabActor);
	RGripStick(grabActor);
	RGripFistAxe(grabActor);
	RGripHalfRock(grabActor);
}

void UGrabActorComponent::RightReleaseAction()
{
	//UE_LOG(LogTemp, Warning, TEXT("44444444444444444444444444444444444444444444"));
	//if (bisRightGrab == true)
	//{
	if (fireRockR)
	{
		fireRockR->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		fireRockR->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		fireRockR->boxComp->SetSimulatePhysics(true);
		fireRockR->outLine->SetVisibility(true);

		fireRockR = nullptr;
		bisRightGrab = false;

		// ������ �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueRight = 0.0f;

		bisGrabFR = true;
	}

	if (fireRock2R)
	{
		fireRock2R->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		fireRock2R->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		fireRock2R->boxComp->SetSimulatePhysics(true);
		fireRock2R->outLine->SetVisibility(true);

		fireRock2R = nullptr;
		bisRightGrab = false;

		// ������ �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueRight = 0.0f;

		bisGrabFR = true;
	}


	if (firePositionR)
	{
		firePositionR->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		firePositionR->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		firePositionR->boxComp->SetSimulatePhysics(true);

		firePositionR = nullptr;
		bisLeftGrab = false;

		// ������ �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueRight = 0.0f;
	}

	if (appleR)
	{
		appleR->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		appleR->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		appleR->boxComp->SetSimulatePhysics(true);

		appleR = nullptr;
		bisLeftGrab = false;
		bisGrabApple = false;

		// ������ �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueRight = 0.0f;
	}

	if (stickR)
	{
		stickR->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		stickR->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		stickR->boxComp->SetSimulatePhysics(false);


		stickR = nullptr;
		bisLeftGrab = false;
		bisStickR = false;

		// ������ �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueRight = 0.0f;
	}

	if (fistAxeR)
	{
		if(fistAxe->bisD1 == false)
		{
		player->rightHand->SetHiddenInGame(false);
		fistAxe->fakeHand->SetHiddenInGame(true);
		}

		if(fistAxe->bisD1 == true)
		{
			fistAxeR->fist->SetEnableGravity(true);
			// �� �ڸ����� ��������
			fistAxeR->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			fistAxeR->fist->SetSimulatePhysics(false);


			fistAxeR = nullptr;
			bisLeftGrab = false;
			bisfistAxeR = false;
		}
		// �ϼ� �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueRight = 0.0f;
	}

	if (halfRock)
	{
		if (fistAxe->bisD1 == true)
		{
			halfRock->halfRock->SetEnableGravity(true);
			// �� �ڸ����� ��������
			halfRock->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			halfRock->halfRock->SetSimulatePhysics(true);

			halfRock = nullptr;
			bisLeftGrab = false;
			bisGrabHR = true;


			// ������ �Ǵ� �ִϸ��̼�
			player->handComp->targetGripValueRight = 0.0f;
		}
	}
	//}
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
	LGripFireRock2(grabActor);
	LGripFirePosition(grabActor);
	LGripApple(grabActor);
	LGripStick(grabActor);
	LGripFistAxe(grabActor);
}

void UGrabActorComponent::LeftReleaseAction()
{
	//if (bisLeftGrab == true)
	//{
	if (fireRockL)
	{
		fireRockL->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		fireRockL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		fireRockL->boxComp->SetSimulatePhysics(true);
		fireRockL->outLine->SetVisibility(true);

		fireRockL = nullptr;
		bisLeftGrab = false;
		bisGrabFR = false;

		// �޼� �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueLeft = 0.0f;
	}

	if (fireRock2L)
	{
		fireRock2L->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		fireRock2L->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		fireRock2L->boxComp->SetSimulatePhysics(true);
		fireRock2L->outLine->SetVisibility(true);

		fireRock2L = nullptr;
		bisRightGrab = false;

		// ������ �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueRight = 0.0f;

		bisGrabFR = true;
	}

	if (firePositionL)
	{
		firePositionL->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		firePositionL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		firePositionL->boxComp->SetSimulatePhysics(true);

		firePositionL = nullptr;
		bisLeftGrab = false;

		// �޼� �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueLeft = 0.0f;
	}

	if (appleL)
	{
		appleL->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		appleL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		appleL->boxComp->SetSimulatePhysics(true);

		appleL = nullptr;
		bisLeftGrab = false;
		bisGrabApple = false;

		// �ϼ� �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueLeft = 0.0f;
	}

	if (stickL)
	{
		stickL->boxComp->SetEnableGravity(true);
		// �� �ڸ����� ��������
		stickL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		stickL->boxComp->SetSimulatePhysics(false);

		stickL = nullptr;
		bisLeftGrab = false;

		// �ϼ� �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueLeft = 0.0f;
	}

	if (fistAxeL)
	{
		fistAxeL->fist->SetEnableGravity(true);
		// �� �ڸ����� ��������
		fistAxeL->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		fistAxeL->fist->SetSimulatePhysics(true);

		fistAxeL->fakeHand->SetHiddenInGame(true);
		player->rightHand->SetHiddenInGame(false);

		fistAxeL = nullptr;
		bisLeftGrab = false;
		bisGrabFistAxeL = false;

		// �ϼ� �Ǵ� �ִϸ��̼�
		player->handComp->targetGripValueLeft = 0.0f;
	}


	//}
		// �޼� �Ǵ� �ִϸ��̼�
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
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			fireRockR->boxComp->SetSimulatePhysics(false);
			fireRockR->boxComp->SetEnableGravity(false);
			fireRockR->outLine->SetVisibility(false);


			fireRockR->AttachToComponent(player->rightHandLoc, attachRules, TEXT("RGrabPoint"));
			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueRight = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			fireRockR->boxComp->SetRelativeLocation((fireRockR->grabOffset));

			bisGrabFR = true;
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

			fireRockL->boxComp->SetSimulatePhysics(false);
			fireRockL->boxComp->SetEnableGravity(false);
			fireRockL->outLine->SetVisibility(false);

			fireRockL->AttachToComponent(player->leftHandLoc, attachRules, TEXT("LGrabPoint"));
			// �޼� ��� �ִϸ��̼�
			player->handComp->targetGripValueLeft = 0.7f;


			// ������Ʈ�� ������� ��ġ ���
			fireRockL->boxComp->SetRelativeLocation((fireRockL->grabOffset));

			bisGrabFR = true;
		}
	}
	//}
}

void UGrabActorComponent::LGripFireRock2(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("BP_FireRock2"))
	{
		fireRock2L = Cast<AFireRock2>(grabActor);

		if (fireRock2L)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			fireRock2L->boxComp->SetSimulatePhysics(false);
			fireRock2L->boxComp->SetEnableGravity(false);
			fireRock2L->outLine->SetVisibility(false);

			fireRock2L->AttachToComponent(player->leftHandLoc, attachRules, TEXT("LGrabPoint"));
			// �޼� ��� �ִϸ��̼�
			player->handComp->targetGripValueLeft = 0.7f;


			// ������Ʈ�� ������� ��ġ ���
			fireRock2L->boxComp->SetRelativeLocation((fireRock2L->grabOffset));

			bisGrabFR = true;
		}
	}
}

void UGrabActorComponent::RGripFireRock2(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("BP_FireRock2"))
	{
		fireRock2R = Cast<AFireRock2>(grabActor);

		if (fireRock2R)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			fireRock2R->boxComp->SetSimulatePhysics(false);
			fireRock2R->boxComp->SetEnableGravity(false);
			fireRock2R->outLine->SetVisibility(false);

			fireRock2R->AttachToComponent(player->rightHandLoc, attachRules, TEXT("RGrabPoint"));
			// �޼� ��� �ִϸ��̼�
			player->handComp->targetGripValueRight = 0.7f;


			// ������Ʈ�� ������� ��ġ ���
			fireRock2R->boxComp->SetRelativeLocation((fireRock2R->grabOffset));

			bisGrabFR = true;
		}
	}
}

void UGrabActorComponent::RGripFirePosition(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("Position"))
	{
		firePositionR = Cast<AFirePosition>(grabActor);

		if (firePositionR)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			firePositionR->boxComp->SetSimulatePhysics(false);
			firePositionR->boxComp->SetEnableGravity(true);


			firePositionR->AttachToComponent(player->rightHandLoc, attachRules, TEXT("RGrabPoint"));
			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueRight = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			firePositionR->boxComp->SetRelativeLocation((firePositionR->grabOffset));

		}
	}
}

void UGrabActorComponent::LGripFirePosition(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("Position"))
	{
		firePositionL = Cast<AFirePosition>(grabActor);

		if (firePositionL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			firePositionL->boxComp->SetSimulatePhysics(false);
			firePositionL->boxComp->SetEnableGravity(true);


			firePositionL->AttachToComponent(player->leftHandLoc, attachRules, TEXT("RGrabPoint"));
			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueLeft = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			firePositionL->boxComp->SetRelativeLocation((firePositionL->grabOffset));

		}
	}
}

void UGrabActorComponent::RGripApple(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("Apple"))
	{
		appleR = Cast<AApple>(grabActor);

		if (appleR)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			appleR->boxComp->SetSimulatePhysics(false);
			appleR->boxComp->SetEnableGravity(true);

			stemR->midLoc->SetSimulatePhysics(true);
			stemR->midLoc->SetEnableGravity(true);
			stemL->midLoc->SetSimulatePhysics(true);
			stemL->midLoc->SetEnableGravity(true);

			stemR->bottomLoc->SetSimulatePhysics(true);
			stemR->bottomLoc->SetEnableGravity(true);
			stemL->bottomLoc->SetSimulatePhysics(true);
			stemL->bottomLoc->SetEnableGravity(true);


			appleR->AttachToComponent(player->rightHandLoc, attachRules, TEXT("RGrabPoint"));

			bisGrabApple = true;

			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueRight = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			appleR->boxComp->SetRelativeLocation((appleR->grabOffset));

		}
	}
}

void UGrabActorComponent::LGripApple(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("Apple"))
	{
		appleL = Cast<AApple>(grabActor);

		if (appleL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			appleL->boxComp->SetSimulatePhysics(false);
			appleL->boxComp->SetEnableGravity(true);

			stemR->midLoc->SetSimulatePhysics(true);
			stemR->midLoc->SetEnableGravity(true);
			stemL->midLoc->SetSimulatePhysics(true);
			stemL->midLoc->SetEnableGravity(true);

			stemR->bottomLoc->SetSimulatePhysics(true);
			stemR->bottomLoc->SetEnableGravity(true);
			stemL->bottomLoc->SetSimulatePhysics(true);
			stemL->bottomLoc->SetEnableGravity(true);


			appleL->AttachToComponent(player->leftHandLoc, attachRules, TEXT("LGrabPoint"));

			bisGrabApple = true;

			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueLeft = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			appleL->boxComp->SetRelativeLocation((appleL->grabOffset));

		}
	}
}

void UGrabActorComponent::RGripStick(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("Stick"))
	{
		stickR = Cast<AStick>(grabActor);

		if (stickR)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			stickR->boxComp->SetSimulatePhysics(false);
			stickR->boxComp->SetEnableGravity(false);


			stickR->AttachToComponent(player->rightHandLoc, attachRules, TEXT("RGrabPoint"));
			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueRight = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			stickR->boxComp->SetRelativeLocation((stickR->grabOffset));

			// �����տ� stick�� �ֳ�?
			bisStickR = true;
		}
	}
}

void UGrabActorComponent::LGripStick(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)
	{*/
	if (fr.Contains("Stick"))
	{
		stickL = Cast<AStick>(grabActor);

		if (stickL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			stickL->boxComp->SetSimulatePhysics(false);
			stickL->boxComp->SetEnableGravity(false);

			stickL->AttachToComponent(player->leftHandLoc, attachRules, TEXT("LGrabPoint"));
			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueLeft = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			stickL->boxComp->SetRelativeLocation((stickL->grabOffset));

			// �����տ� stick�� �ֳ�?
			bisStickL = true;
		}
	}
}

void UGrabActorComponent::LGripFistAxe(AActor* grabActor)
{
	FString fr = grabActor->GetName();

	if (fr.Contains("FistAxe"))
	{
		fistAxeL = Cast<AFistAxe>(grabActor);

		if (fistAxeL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
			//fireRock->SetActorHiddenInGame(false);
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			fistAxeL->fist->SetSimulatePhysics(false);
			fistAxeL->fist->SetEnableGravity(false);


			fistAxeL->AttachToComponent(player->leftFALoc, attachRules, TEXT("LFAPoint"));
			// ������ ��� �ִϸ��̼�
			player->handComp->targetGripValueLeft = 0.7f;

			// ������Ʈ�� ������� ��ġ ���
			fistAxeL->fist->SetRelativeLocation((fistAxeL->grabOffset));

			fistAxeL->handHologramL->SetHiddenInGame(true);
			fistAxeL->handHologramR->SetHiddenInGame(false);

			bisGrabFistAxeL = true;

		}

		if (fistAxe->bisD1 == true)
		{
			fistAxeL->handHologramR->SetHiddenInGame(true);
		}
	}
}

void UGrabActorComponent::RGripFistAxe(AActor* grabActor)
{
	FString fr = grabActor->GetName();

	if (fr.Contains("FistAxe"))
	{
		fistAxeR = Cast<AFistAxe>(grabActor);

		if (fistAxe->bisD1 == false)
		{
			if (fistAxeR)
			{
				fistAxeR->fist->SetSimulatePhysics(false);
				fistAxeR->fist->SetEnableGravity(false);

				fistAxeR->handHologramR->SetHiddenInGame(true);
				fistAxeR->fakeHand->SetHiddenInGame(false);
				player->rightHand->SetHiddenInGame(true);
				bisGrabFistAxeR = true;

			}
		}


		if (fistAxe->bisD1 == true)
		{
			if (fistAxeR)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
				//fireRock->SetActorHiddenInGame(false);
				//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
				FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

				fistAxeR->fist->SetSimulatePhysics(false);
				fistAxeR->fist->SetEnableGravity(false);


				fistAxeR->AttachToComponent(player->rightFALoc, attachRules, TEXT("RGrabPoint"));
				// ������ ��� �ִϸ��̼�
				player->handComp->targetGripValueRight = 0.7f;

				// ������Ʈ�� ������� ��ġ ���
				fistAxeR->fist->SetRelativeLocation((fistAxeR->grabOffset));

				fistAxeR->fakeHand->SetHiddenInGame(true);

				bisGrabFistAxeR = true;

			}
		}
	}
}

void UGrabActorComponent::RGripHalfRock(AActor* grabActor)
{
	FString fr = grabActor->GetName();
	/*if (fireRock == nullptr)0
	{*/

	if (bisGrabFistAxeL == true)
	{
		if (fr.Contains("HalfRock"))
		{
			halfRock = Cast<AHalfRock>(grabActor);

			if (halfRock)
			{
				if (fistAxeL->bisD1 == true)
				{
					//UE_LOG(LogTemp, Warning, TEXT("3333333333333333333333333333333333333333333333"));
							//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TRIGGER IN!!")));
							//fireRock->SetActorHiddenInGame(false);
							//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
					FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepRelativeTransform;

					halfRock->halfRock->SetSimulatePhysics(false);
					halfRock->halfRock->SetEnableGravity(false);


					halfRock->AttachToComponent(player->rightHRLoc, attachRules, TEXT("RGrabPoint"));
					// ������ ��� �ִϸ��̼�
					player->handComp->targetGripValueRight = 0.3f;

					// ������Ʈ�� ������� ��ġ ���
					halfRock->halfRock->SetRelativeLocation((halfRock->grabOffset));
				}
			}
		}
	}
}