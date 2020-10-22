// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonPawn.h"

// Sets default values
ADragonPawn::ADragonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsIdle = true;
	OnGround = true;
	TakeOff = false;
	Land = false;

	RotationRate = 140;
}

// Called when the game starts or when spawned
void ADragonPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADragonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADragonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ADragonPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&ADragonPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&ADragonPawn::LookUpRate);


}

void ADragonPawn::MoveForward(float axis)
{

	AddMovementInput(GetActorForwardVector()*axis);

}

void ADragonPawn::MoveRight(float axis)
{
	AddMovementInput(GetActorRightVector()*axis);
}

void ADragonPawn::LookUpRate(float axis)
{

	AddControllerPitchInput(axis * RotationRate * GetWorld()->DeltaTimeSeconds);

}