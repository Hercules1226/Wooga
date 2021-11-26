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
	// Body 높이
	capsuleComp->SetCapsuleHalfHeight(65.0f);
	// Body 각도
	capsuleComp->SetCapsuleRadius(40.0f);
	// Player Collision Setting
	capsuleComp->SetCollisionProfileName(TEXT("VR_Player"));

	// Camera Location 생성
	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	// CapsuleComp 에 붙임
	cameraRoot->SetupAttachment(RootComponent);
	// Camera Location
	cameraRoot->SetRelativeLocation(FVector(0, 0, 30.0f));

	// Main Camera 생성
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	// Camera Location 에 붙임
	playerCam->SetupAttachment(cameraRoot);

	camLoc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CamLoc"));
	// Camera Location 에 붙임
	camLoc->SetupAttachment(playerCam);

	camLookAt = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CamLookAt"));
	// Camera Location 에 붙임
	camLookAt->SetupAttachment(playerCam);

	headComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Head Component"));
	headComp->SetupAttachment(cameraRoot);
	//headComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mouthComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Mouth Component"));
	mouthComp->SetupAttachment(cameraRoot);

	// LeftController 생성
	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	// Camera Location 에 붙임
	leftController->SetupAttachment(cameraRoot);
	// 왼손으로 등록
	leftController->MotionSource = "Left";

	// RightController 생성
	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	// Camera Location 에 붙임
	rightController->SetupAttachment(cameraRoot);
	// 오른손으로 등록
	rightController->MotionSource = "Right";


	// 왼손 Skeletal 생성
	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	// LeftController 에 붙임
	leftHand->SetupAttachment(leftController);
	// 오른손 Skeletal 을 가져와서 왼손으로 바꾸기 위해 뒤집음
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	// 왼손의 Scale 값
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.0f, 1.0f));

	playerWatch = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerWatch"));
	playerWatch->SetupAttachment(leftHand);
	playerWatch->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));


	// 왼손으로 물체를 잡을때의 위치 값
	leftHandLoc = CreateDefaultSubobject<USceneComponent>(TEXT("LeftHandLoc"));
	// 왼손에 붙여줌
	leftHandLoc->SetupAttachment(leftHand);
	// 물체를 잡을때의 Location 값 
	leftHandLoc->SetRelativeLocation(FVector(10.f, 0.f, -3.f));
	// 물체를 잡을때의 Rotation 값
	leftHandLoc->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	// 왼손으로 물체를 잡을때의 위치 값
	leftFALoc = CreateDefaultSubobject<USceneComponent>(TEXT("LeftFALoc"));
	// 왼손에 붙여줌
	leftFALoc->SetupAttachment(leftHand);
	// 물체를 잡을때의 Location 값 
	leftFALoc->SetRelativeLocation(FVector(10.f, 0.f, -3.f));
	// 물체를 잡을때의 Rotation 값
	leftFALoc->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	// 오른손 Skeletal 생성
	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	//RightController 에 붙임
	rightHand->SetupAttachment(rightController);
	// 오른손의 Scale 값
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));



	// 오른손으로 물체를 잡을때의 위치 값
	rightHandLoc = CreateDefaultSubobject<USceneComponent>(TEXT("RightHandLoc"));
	// 오른손에 붙여줌
	rightHandLoc->SetupAttachment(rightHand);
	// 물체를 잡을때의 Location 값 
	rightHandLoc->SetRelativeLocation(FVector(10.f, 0.f, -3.f));
	// 물체를 잡을때의 Rotation 값
	rightHandLoc->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	// 오른손으로 물체를 잡을때의 위치 값
	rightFALoc = CreateDefaultSubobject<USceneComponent>(TEXT("RightFALoc"));
	// 오른손에 붙여줌
	rightFALoc->SetupAttachment(rightHand);
	// 물체를 잡을때의 Location 값 
	rightFALoc->SetRelativeLocation(FVector(10.f, 0.f, -3.f));
	// 물체를 잡을때의 Rotation 값
	rightFALoc->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	// 오른손으로 물체를 잡을때의 위치 값
	rightHRLoc = CreateDefaultSubobject<USceneComponent>(TEXT("RightHRLoc"));
	// 오른손에 붙여줌
	rightHRLoc->SetupAttachment(rightHand);
	// 물체를 잡을때의 Location 값 
	rightHRLoc->SetRelativeLocation(FVector(10.f, 0.f, -3.f));
	// 물체를 잡을때의 Rotation 값
	rightHRLoc->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	// 오른쪽 손목 위 3D TEXT 
	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightController);
	// Text Size
	rightLog->SetWorldSize(10);
	// 글씨 정렬 (가운데 정렬)
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	rightLog->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	// 글씨 색상
	rightLog->SetTextRenderColor(FColor::Yellow);

	// 액터 컴포넌트들
	moveComp = CreateDefaultSubobject<UMoveActorComponent>(TEXT("MoveComponent"));
	handComp = CreateDefaultSubobject<UHandActorComponent>(TEXT("HandComponent"));
	grabComp = CreateDefaultSubobject<UGrabActorComponent>(TEXT("GrabComponent"));

	//플레이어 컨트롤러 빙의
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();

	// HMD 의 초기 위치값을 설정하기
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotation, hmdLocation);
	// HMD 의 기준점을 바닥으로 설정
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
	// HMD 의 위치를 초기화하기
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();

	isClose = false;

	playerWatch->SetHiddenInGame(true);

	// playerWatch->OnComponentBeginOverlap.AddDynamic(this, &AVR_Player::OverlapKnowledgePoint);


}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(headRotate, headLocation);
	
	headRotateYaw = headRotate.Yaw;
	headRotatePitch = headRotate.Pitch;

	headComp->SetRelativeLocation(headLocation);
	mouthComp->SetRelativeLocation(headLocation);

	headComp->SetRelativeRotation(FRotator(headRotatePitch, headRotateYaw, 0.f));
	mouthComp->SetRelativeRotation(FRotator(headRotatePitch, headRotateYaw, 0.f));
	// mouthComp->SetRelativeRotation(FRotator(0.f, headRotateYaw, 0.f));

	// UI 닫는 버튼을 누르면 시간이 흐를 수 있게 한다
	if (isClose == true)
	{
		bIsCloseDelay = true;
	}

	// 시간이 흐르기 시작하면
	if (bIsCloseDelay == true)
	{
		change += DeltaTime;

		// 0.1 초가 지나면 UI 애니메이션을 실행 할 수 있게 해준다.
		if (change >= 0.1f)
		{
			isClose = false;
		}
		// 2.1초가 지나면 다시 버튼을 활성화 해준다.
		if (change >= 2.1f)
		{
			change = 0;
			bIsCloseDelay = false;
			UE_LOG(LogTemp, Warning, TEXT("Can Off UI"));
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
		// 불의 발견
		if (knowledgePoint == 0)
		{
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);
			knowledgePoint = 1;
			isKnowledgeIn = true;
			isPlayAnim = true;
			OtherActor->Destroy();
		}
		// 채집
		else if (knowledgePoint == 1)
		{
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);
			knowledgePoint = 2;
			isKnowledgeIn = true;
			isPlayAnim = true;
			OtherActor->Destroy();
		}
		// 주먹도끼
		else if(knowledgePoint == 2)
		{
			GetWorld()->GetFirstPlayerController()->PlayHapticEffect(watchHaptic, EControllerHand::Left, 0.5f, false);
			knowledgePoint = 3;
			isKnowledgeIn = true;
			isPlayAnim = true;
			OtherActor->Destroy();
		}
	}
}

void AVR_Player::TurnOff()
{
	if (isClose == false && bIsCloseDelay == false)
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

