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

	// �÷��̾�
	class AVR_Player* player;
	// �ָԵ���
	class AFistAxe* fistAxe;

	// ���� ���� �ӽ�
	EBoarState boarState;
	// ĸ��ȭ
	void SetState(EBoarState state);
	EBoarState GetState();

	// ���¸ӽ� �Լ�
	void Run();
	void SlowMotion();
	void Hit();
	void Die();

	// ���� ��ġ
	FVector me;
	// �÷��̾� ��ġ
	FVector playerLoc;
	// �÷��̾� - ����
	FVector dir;
	// ���� �޸��� �ӵ� ����
	UPROPERTY()
	float speed = 300.0f;

	// ���ο� ��Ǳ��� �ð�
	UPROPERTY()
	float slowTime;

	// �÷��̾�� �������� �Ÿ� ����
	UPROPERTY()
	float distance = 250.0f;

	// ������ �Լ�
	UFUNCTION()
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
