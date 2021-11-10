// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActorComponent.h"
#include "VR_Player.h"
#include "MotionControllerComponent.h"
#include "VRHandAnimInstance.h"
#include "HandActorComponent.h"
#include <Camera/CameraComponent.h>
#include "SJ_WoogaGameModeBase.h"

// Sets default values for this component's properties
UMoveActorComponent::UMoveActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(GetOwner());

	// 게임모드 캐싱
	gameMode = Cast<ASJ_WoogaGameModeBase>(GetWorld()->GetAuthGameMode());

}


// Called every frame
void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UMoveActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("RightThumbstick_X", this, &UMoveActorComponent::MoveHorizontal);
	PlayerInputComponent->BindAxis("RightThumbstick_Y", this, &UMoveActorComponent::MoveVertical);
	PlayerInputComponent->BindAxis("LeftThumbstick_X", this, &UMoveActorComponent::RotateHorizontal);
	PlayerInputComponent->BindAction("LeftGrip", IE_Pressed, this, &UMoveActorComponent::LeftGripOn);
	PlayerInputComponent->BindAction("LeftGrip", IE_Released, this, &UMoveActorComponent::LeftGripOff);
	PlayerInputComponent->BindAction("RightGrip", IE_Pressed, this, &UMoveActorComponent::RightGripOn);
	PlayerInputComponent->BindAction("RightGrip", IE_Released, this, &UMoveActorComponent::RightGripOff);
}

void UMoveActorComponent::MoveHorizontal(float value)
{

	if (bisMove == true)
	{
		FVector dir = player->GetActorRightVector() * value;

		player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
	}
}

void UMoveActorComponent::MoveVertical(float value)
{
	if (bisMove == true)
	{
		//auto cam = Cast<UCameraComponent>(player->GetDefaultSubobjectByName(TEXT("MainCamera")));

		FVector dir = player->GetActorForwardVector() * value;
		dir.Z = 0;

		player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
	}
}

void UMoveActorComponent::RotateHorizontal(float value)
{
	if (bisMove == true)
	{
		FRotator rot = FRotator(0, value * rotateSpeed * GetWorld()->DeltaTimeSeconds, 0);
		player->AddActorLocalRotation(rot);
	}
}

void UMoveActorComponent::LeftGripOn()
{
	player->handComp->targetGripValueLeft = 1.0f;
}

void UMoveActorComponent::LeftGripOff()
{
	player->handComp->targetGripValueLeft = 0.0f;
}

void UMoveActorComponent::RightGripOn()
{
	player->handComp->targetGripValueRight = 1.0f;

}

void UMoveActorComponent::RightGripOff()
{
	player->handComp->targetGripValueRight = 0.0f;
}

