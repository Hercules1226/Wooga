// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wooga.h"
#include "GameFramework/Actor.h"
#include "SJ_Actor_Title.generated.h"

UCLASS()
class WOOGA_API ASJ_Actor_Title : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASJ_Actor_Title();

	UPROPERTY(EditAnywhere, Category = Title)
	class UStaticMeshComponent* title;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ASJ_WoogaGameModeBase* gameMode;

	// ���� ���¸ӽ�
	ETitleState titleState;
	ETitleState GetState();
	void SetState(ETitleState state);

	void OnTitle();
	void StayTitle();
	void OffTitle();

	// �÷��̽ð�
	UPROPERTY()
	float playTime;

	// ���� �Ķ����
	UPROPERTY()
	float startParam;
	UPROPERTY()
	float endParam;

	// �������
	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* titleSound;
};
