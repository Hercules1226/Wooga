// Fill out your copyright notice in the Description page of Project Settings.


#include "Default_Pawn.h"

// Sets default values
ADefault_Pawn::ADefault_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefault_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefault_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefault_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

