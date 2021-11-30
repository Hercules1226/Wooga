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
	// Capsule 몸체
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UCapsuleComponent* capsuleComp;
	// Camera 위치
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* cameraRoot;
	// Main Camera
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UCameraComponent* playerCam;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UStaticMeshComponent* camLoc;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UStaticMeshComponent* camLookAt;

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
	// 왼손
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USkeletalMeshComponent* leftHand;
	// 왼손 그랩 포인트
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* leftHandLoc;
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* leftFALoc;
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* leftSRLoc;
	// 오른손
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USkeletalMeshComponent* rightHand;
	// 오른손 그랩 포인트
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* rightHandLoc;
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* rightFALoc;
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class USceneComponent* rightHRLoc;
	// 왼손 그랩 TextLog
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* leftLog;
	// 오른손 그랩 TextLog
	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UTextRenderComponent* rightLog;

	UPROPERTY(EditAnywhere, Category = Watch)
		class UWidgetComponent* playerWatch;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
		class UStaticMeshComponent* watch;

	// 액터 컴포넌트들 추가하기
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
		class UMoveActorComponent* moveComp;

	// 손 애니메이션 추가
	UPROPERTY(VisibleAnywhere, Category = PlayerSettings)
		class UHandActorComponent* handComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		class UGrabActorComponent* grabComp;

	UPROPERTY()
		class ASJ_UIPannel* uiPannel;

	void TurnOff();

	UPROPERTY(VisibleDefaultsOnly, Category = state)
		bool isClose;

	UPROPERTY()
		bool bIsCloseDelay;

public:
	void ResetHMD();

	UPROPERTY()
		FRotator hmdRotation;
	UPROPERTY()
		FVector hmdLocation;

	UPROPERTY()
		FRotator hmdRotation2;
	UPROPERTY()
		FVector hmdLocation2;

	UPROPERTY()
		FRotator headRotate;
	UPROPERTY()
		FVector headLocation;

	UPROPERTY()
		float headRotateYaw;
	UPROPERTY()
		float headRotatePitch;

	UPROPERTY()
		float change;

	UPROPERTY(VisibleAnywhere, Category = knowledge)
		float knowledgePoint;

	UPROPERTY()
		FTimerHandle testTimer;

	UPROPERTY()
	bool isKnowledgeIn;

	UFUNCTION()
		void OverlapKnowledgePoint(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		bool isPlayAnim;

	UPROPERTY(EditAnywhere, Category = Haptic)
		class UHapticFeedbackEffect_Base* watchHaptic;
};
