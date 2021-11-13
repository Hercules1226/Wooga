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

	// �÷��̾�
	class AVR_Player* player;
	// �ָԵ���
	class AFistAxe* fistAxe;
	// AnimInstance
	class USJ_BoarAnimInstance* anim;

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
	float distance = 350.0f;

	// ���� ���� ����
	UPROPERTY()
	bool isHitBoar;

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

	// ������ �Լ�
	UFUNCTION()
	void HitPointTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HitBoarBody(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FActorSpawnParameters Param;
	UPROPERTY(EditAnywhere, Category = SlicePig)
	TSubclassOf<class ASlicePig> bpSlicePig;

};
