// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	class AFireRock* fireRockR;
	class AFireRock* fireRockL;

private:
	void ShowGrabLine();
	void HideGrabLine();
	void RightDrawGrabLine();
	void LeftDrawGrabLine();
	void RightGrabAction();
	void RightReleaseAction();
	void LeftGrabAction();
	void LeftReleaseAction();

	// ��� ���͵�
	void RGripFireRock(AActor* grabActor);
	void LGripFireRock(AActor* grabActor);

	void RGripFirePosition(AActor* grabActor);
	void LGripFirePosition(AActor* grabActor);

	void RGripApple(AActor* grabActor);
	void LGripApple(AActor* grabActor);


	bool bIsShowing = false;
	bool bisRightGrab = false;
	bool bisLeftGrab = false;
	class AVR_Player* player;
	
	class AFirePosition* firePositionR;
	class AFirePosition* firePositionL;
	class AApple* appleR;
	class AApple* appleL;

	FHitResult grabObject;

public:
	UPROPERTY(EditAnywhere, Category = AAA)
		FVector grabOffset;

	UPROPERTY(EditAnywhere, Category = AAA)
		float grabRange = 15;
};
