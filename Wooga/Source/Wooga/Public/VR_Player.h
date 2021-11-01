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
		UPROPERTY(EditAnywhere, Category = PickUPSettings)
			class UBoxComponent* headComp;

		UPROPERTY(EditAnywhere, Category = PickUPSettings)
			class UBoxComponent* mouthComp;

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
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USceneComponent* leftFALoc;
		// ������
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USkeletalMeshComponent* rightHand;
		// ������ �׷� ����Ʈ
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USceneComponent* rightHandLoc;
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USceneComponent* rightFALoc;
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class USceneComponent* rightHRLoc;
		// �޼� �׷� TextLog
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class UTextRenderComponent* leftLog;
		// ������ �׷� TextLog
		UPROPERTY(EditAnywhere, Category = PlayerSettings)
			class UTextRenderComponent* rightLog;

		UPROPERTY(EditAnywhere, Category = Watch)
			class UWidgetComponent* playerWatch;

		// ���� ������Ʈ�� �߰��ϱ�
		UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
			class UMoveActorComponent* moveComp;

		// �� �ִϸ��̼� �߰�
		UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
			class UHandActorComponent* handComp;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerSettings)
			class UGrabActorComponent* grabComp;

		UPROPERTY()
			class ASJ_UIPannel* uiPannel;

		void TurnOff();

		UPROPERTY(VisibleDefaultsOnly, Category = state)
			bool isClose;

public:
	void ResetHMD();
	

	FRotator hmdRotation;
	FVector hmdLocation;

	FRotator hmdRotation2;
	FVector hmdLocation2;

	FRotator headRotate;
	FVector headLocation;

	float headRotateYaw;
	float headRotatePitch;


	float change;

	UPROPERTY(VisibleAnywhere, Category = knowledge)
		float knowledgePoint;

	FTimerHandle testTimer;

	UFUNCTION()
		void OverlapKnowledgePoint(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		bool isPlayAnim;

	UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;
};
