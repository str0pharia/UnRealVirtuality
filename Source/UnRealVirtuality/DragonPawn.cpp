// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
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

	DragonMesh = (USkeletalMeshComponent*)GetDefaultSubobjectByName(FName("Mesh"));

}

// Called when the game starts or when spawned
void ADragonPawn::BeginPlay()
{
	Super::BeginPlay();
	AIState = EDragonAIState::IDLE_WAIT;
	PrevAIState = AIState;
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

void ADragonPawn::Update(float DeltaTime)
{


	/*
	if ( OnGround && d >= Z_THRESHOLD ) 
	{
		OnGround = false;
		GetMesh()->SetEnableGravity(false);

	}
	else if ( !OnGround && d < Z_THRESHOLD ) 
	{
		OnGround = true;
		GetMesh()->SetEnableGravity(true);

	}

	if ( AIState == EDragonAIState::IDLE_WAIT && !GetVelocity().IsZero() )
	{

		TransitionToState( EDragonAIState::MOVE );

	}

	*/
}
bool ADragonPawn::TransitionToState(EDragonAIState s)
{

	EDragonAIState t = SetAIState(s);

	return (s != t);

	
}

float ADragonPawn::DistanceToGround()
{
	FHitResult Hit;

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() - (GetActorUpVector() * TRACE_DISTANCE), ECollisionChannel::ECC_WorldStatic);
	return (bHit) ? Hit.Distance : TRACE_DISTANCE;
}

EDragonAIState ADragonPawn::GetAIState() 
{

	return AIState;
}

EDragonAIState ADragonPawn::SetAIState(EDragonAIState s) 
{
	if ( s != AIState)
	{
		PrevAIState = AIState;
		AIState = s;
	}

	return AIState;
}

/* Called from BP when notified by animation BP */
void ADragonPawn::OnMovementModeChanged(bool walk)
{

		OnGround = walk;

		if ( nullptr != DragonMesh )
		{
			//DragonMesh->SetEnableGravity(walk);
		
		}



}