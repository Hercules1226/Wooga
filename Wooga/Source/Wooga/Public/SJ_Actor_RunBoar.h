// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_RunBoar.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_RunBoar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_RunBoar();

	UPROPERTY(EditAnywhere, Category = Boar)
	class USceneComponent* rootComp;

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

	// 플레이어
	class AVR_Player* player;
	// 주먹도끼
	class AFistAxe* fistAxe;

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
	float distance = 250.0f;

	// 오버랩 함수
	UFUNCTION()
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
