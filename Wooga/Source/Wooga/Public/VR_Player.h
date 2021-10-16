// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VR_Player.generated.h"

UCLASS()
class WOOGA_API AVR_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVR_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
		// Capsule ��ü
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class UCapsuleComponent* capsuleComp;
		// Camera ��ġ
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USceneComponent* cameraRoot;
		// Main Camera
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class UCameraComponent* playerCam;
		// LeftController
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
			class UMotionControllerComponent* leftController;
		// RightController
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
			class UMotionControllerComponent* rightController;
		// �޼�
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USkeletalMeshComponent* leftHand;
		// �޼� �׷� ����Ʈ
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USceneComponent* leftHandLoc;
		// ������
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USkeletalMeshComponent* rightHand;
		// ������ �׷� ����Ʈ
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USceneComponent* rightHandLoc;
		// �޼� �׷� TextLog
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class UTextRenderComponent* leftLog;
		// ������ �׷� TextLog
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class UTextRenderComponent* rightLog;


		// ���� ������Ʈ�� �߰��ϱ�
		UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
			class UMoveActorComponent* moveComp;

		// �� �ִϸ��̼� �߰�
		UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
			class UHandActorComponent* handComp;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerSettings)
			class UGrabActorComponent* grabComp;

private:
	void ResetHMD();

	FRotator hmdRotation;
	FVector hmdLocation;		
};
