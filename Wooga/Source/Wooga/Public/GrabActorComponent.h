// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabActorComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WOOGA_API UGrabActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);



public:
	void ShowGrabLine();
	void HideGrabLine();
	void RightDrawGrabLine();
	void LeftDrawGrabLine();
	void RightGrabAction();
	void RightReleaseAction();
	void LeftGrabAction();
	void LeftReleaseAction();


	// 잡는 액터들

	void RGripFireRock(AActor* grabActor);

	void LGripFireRock(AActor* grabActor);

	void RGripFireRock2(AActor* grabActor);

	void LGripFireRock2(AActor* grabActor);

	void RGripFirePosition(AActor* grabActor);

	void LGripFirePosition(AActor* grabActor);

	void RGripApple(AActor* grabActor);

	void LGripApple(AActor* grabActor);

	void RGripStick(AActor* grabActor);

	void LGripStick(AActor* grabActor);

	void LGripFistAxe(AActor* grabActor);

	void RGripFistAxe(AActor* grabActor);

	void RGripHalfRock(AActor* grabActor);


	UPROPERTY()
		class AVR_Player* player;

	// 잡을 액터
	UPROPERTY()
		class AFireRock* fireRockR;
	UPROPERTY()
		class AFireRock* fireRockL;

	UPROPERTY()
		class AFireRock2* fireRock2L;
	UPROPERTY()
		class AFireRock2* fireRock2R;

	UPROPERTY()
		class AFirePosition* firePositionR;
	UPROPERTY()
		class AFirePosition* firePositionL;

	UPROPERTY()
		class AApple* appleR;
	UPROPERTY()
		class AApple* appleL;

	UPROPERTY()
		class AStem* stemR;
	UPROPERTY()
		class AStem* stemL;

	UPROPERTY()
		class AStick* stickR;
	UPROPERTY()
		class AStick* stickL;

	UPROPERTY()
		class AFistAxe* fistAxe;
	UPROPERTY()
		class AFistAxe* fistAxeL;
	UPROPERTY()
		class AFistAxe* fistAxeR;


	UPROPERTY()
		class AHalfRock* halfRock;

	UPROPERTY()
		FHitResult grabObject;

public:
	UPROPERTY(EditAnywhere, Category = AAA)
		FVector grabOffset;

	UPROPERTY(EditAnywhere, Category = AAA)
		float grabRange = 15;

	UPROPERTY()
		bool bIsShowing = false;
	UPROPERTY()
		bool bisRightGrab = false;
	UPROPERTY()
		bool bisLeftGrab = false;
	UPROPERTY()
		bool bisStickR = false;
	UPROPERTY()
		bool bisStickL = false;
	UPROPERTY()
		bool bisGrabApple = false;
	UPROPERTY()
		bool bisGrabFR = false;
	UPROPERTY()
		bool bisGrabFistAxeL = false;
	UPROPERTY()
		bool bisGrabFistAxeR = false;
	UPROPERTY()
		bool bisGrabHR = false;
	UPROPERTY()
		bool bisfistAxeR = false;

};
