// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Character.h"
#include "SJ_Character_Boar.generated.h"

UCLASS()
class WOOGA_API ASJ_Character_Boar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASJ_Character_Boar();

	UPROPERTY(EditAnywhere, Category = Boar)
	class USkeletalMeshComponent* boarMesh;

	UPROPERTY(EditAnywhere, Category = Boar)
	class UStaticMeshComponent* hitPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 플레이어
	class AVR_Player* player;
	// 주먹도끼
	class AFistAxe* fistAxe;
	// AnimInstance
	class USJ_BoarAnimInstance* anim;

	// 돼지 위치
	FVector me;
	// 플레이어 위치
	FVector playerLoc;
	// 플레이어 - 돼지
	FVector dir;

	// 돼지 달리기 속도 변수
	UPROPERTY()
	float speed = 300.0f;
	// 슬로우 모션까지 시간
	UPROPERTY()
	float slowTime;
	// 플레이어와 돼지간의 거리 변수
	UPROPERTY()
	float distance = 100.0f;

	// 돼지 상태 머신
	EBoarState boarState;
	// 캡슐화
	void SetState(EBoarState state);
	EBoarState GetState();

	// 상태머신 함수
	void Run();
	void SlowMotion();
	void Hit();
	void Die();

	// 오버랩 함수
	UFUNCTION()
	void HitPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HitBoarBody(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FActorSpawnParameters Param;
	UPROPERTY(EditAnywhere, Category = SlicePig)
	TSubclassOf<class ASlicePig> bpSlicePig;

};
