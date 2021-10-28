// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "MoveActorComponent.h"
#include "HandActorComponent.h"
#include "GrabActorComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SJ_UIPannel.h"
#include <Kismet/GameplayStatics.h>
#include <DrawDebugHelpers.h>
#include <Components/WidgetComponent.h>
#include "FIreEvent.h"

// Sets default values
AVR_Player::AVR_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Player Body
	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CpasuleCollider"));
	// CapsuleComp = RootComponent
	SetRootComponent(capsuleComp);
	// Body ����
	capsuleComp->SetCapsuleHalfHeight(65.0f);
	// Body ����
	capsuleComp->SetCapsuleRadius(40.0f);
	// Player Collision Setting
	capsuleComp->SetCollisionProfileName(TEXT("VR_Player"));

	// Camera Location ����
	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	// CapsuleComp �� ����
	cameraRoot->SetupAttachment(RootComponent);
	// Camera Location
	cameraRoot->SetRelativeLocation(FVector(0, 0, 30.0f));

	// Main Camera ����
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	// Camera Location �� ����
	playerCam->SetupAttachment(cameraRoot);

	headComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Head Component"));
	headComp->SetupAttachment(cameraRoot);
	//headComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mouthComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Mouth Component"));
	mouthComp->SetupAttachment(cameraRoot);

	// LeftController ����
	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	// Camera Location �� ����
	leftController->SetupAttachment(cameraRoot);
	// �޼����� ���
	leftController->MotionSource = "Left";

	// RightController ����
	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	// Camera Location �� ����
	rightController->SetupAttachment(cameraRoot);
	// ���������� ���
	rightController->MotionSource = "Right";


	// �޼� Skeletal ����
	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	// LeftController �� ����
	leftHand->SetupAttachment(leftController);
	// ������ Skeletal �� �����ͼ� �޼����� �ٲٱ� ���� ������
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	// �޼��� Scale ��
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.0f, 1.0f));

	playerWatch = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerWatch"));
	playerWatch->SetupAttachment(leftHand);
	playerWatch->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));


	// �޼����� ��ü�� �������� ��ġ ��
	leftHandLoc = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandLoc"));
	// �޼տ� �ٿ���
	leftHandLoc->SetupAttachment(leftHand);
	// ��ü�� �������� Location �� 
	leftHandLoc->SetRelativeLocation(FVector(10.f, 0.f, -3.f));
	// ��ü�� �������� Rotation ��
	leftHandLoc->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));



	// ������ Skeletal ����
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	//RightController �� ����
	rightHand->SetupAttachment(rightController);
	// �������� Scale ��
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));



	// ���������� ��ü�� �������� ��ġ ��
	rightHandLoc = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandLoc"));
	// �����տ� �ٿ���
	rightHandLoc->SetupAttachment(rightHand);
	// ��ü�� �������� Location �� 
	rightHandLoc->SetRelativeLocation(FVector(10.f, 0.f, -3.f));
	// ��ü�� �������� Rotation ��
	rightHandLoc->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	// ������ �ո� �� 3D TEXT 
	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightController);
	// Text Size
	rightLog->SetWorldSize(10);
	// �۾� ���� (��� ����)
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	rightLog->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	// �۾� ����
	rightLog->SetTextRenderColor(FColor::Yellow);

	// ���� ������Ʈ��
	moveComp = CreateDefaultSubobject<UMoveActorComponent>(TEXT("MoveComponent"));
	handComp = CreateDefaultSubobject<UHandActorComponent>(TEXT("HandComponent"));
	grabComp = CreateDefaultSubobject<UGrabActorComponent>(TEXT("GrabComponent"));

	//�÷��̾� ��Ʈ�ѷ� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();
	
	// HMD �� �ʱ� ��ġ���� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);
	// HMD �� �������� �ٴ����� ����
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
	// HMD �� ��ġ�� �ʱ�ȭ�ϱ�
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();

	isClose = false;

	playerWatch->SetHiddenInGame(true);

	playerWatch->OnComponentBeginOverlap.AddDynamic(this, &AVR_Player::OverlapKnowledgePoint);

	
}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(headRotate, headLocation);
	headRotateYaw = headRotate.Yaw;
	headRotatePitch = headRotate.Pitch;

	headComp->SetRelativeRotation(FRotator(headRotatePitch, headRotateYaw, 0.f));
	mouthComp->SetRelativeRotation(FRotator(headRotatePitch, headRotateYaw, 0.f));
	// mouthComp->SetRelativeRotation(FRotator(0.f, headRotateYaw, 0.f));

	if (isClose == true)
	{
		change += DeltaTime; 

		if (change >= 0.1f)
		{
			isClose = false;
			change = 0;
		}
	}
}

// Called to bind functionality to input
void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	moveComp->SetupPlayerInputComponent(PlayerInputComponent);
	grabComp->SetupPlayerInputComponent(PlayerInputComponent);

	// Action Bindings
	PlayerInputComponent->BindAction("HMDReset", IE_Pressed, this, &AVR_Player::ResetHMD);
	PlayerInputComponent->BindAction("TurnOffUI", IE_Pressed, this, &AVR_Player::TurnOff);
	//PlayerInputComponent->BindAction("RightTrigger", IE_Pressed, this, &AVR_Player::         );
	//PlayerInputComponent->BindAction("RightGrip", IE_Pressed, this, &AVR_Player::         );

	// Axis Bindings
	//PlayerInputComponent->BindAxis("LeftThumbstick_X", this, &AVR_Player::HorizontalMove);
	//PlayerInputComponent->BindAxis("LeftThumbstick_Y", this, &AVR_Player::VerticalMove);
}

void AVR_Player::ResetHMD()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AVR_Player::OverlapKnowledgePoint(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto fireEvent = Cast<AFireEvent>(OtherActor);
	if (fireEvent)
	{
		knowledgePoint = 1;
		isPlayAnim = true;
		OtherActor->Destroy();
	}
}

void AVR_Player::TurnOff()
{
	if (isClose == false)
	{
		isClose = true;
	}
}

//void AVR_Player::HorizontalMove(float value)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("HEAD!!")));
//}
//
//void AVR_Player::VerticalMove(float value)
//{
//	
//}

