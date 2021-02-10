// Fill out your copyright notice in the Description page of Project Settings.
#include "ObstacleBase.h"
#include "Obstacles.h"
#include "Actor.h"
// Sets default values
AObstacleBase::AObstacleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AObstacleBase::~AObstacleBase()
{


}


// Called when the game starts or when spawned
void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AObstacleBase::IsAffectedByWind() 
{
	return IObstacles::IsAffectedByWind();
}

float AObstacleBase::GetScoreValue() 
{
	return IObstacles::GetScoreValue();
}

TEnumAsByte<EObstacleState> AObstacleBase::GetObstacleState() 
{
	return IObstacles::GetObstacleState();
}

TEnumAsByte<EObstacleType> AObstacleBase::GetObstacleType() 
{
	return IObstacles::GetObstacleType();
}

float AObstacleBase::LosRange(FVector Direction) 
{
	return IObstacles::LosRange(Direction);
}

FVector AObstacleBase::GetMargins() 
{
	return IObstacles::GetMargins();
}

bool AObstacleBase::PlayerDetected()
{
	return IObstacles::PlayerDetected();
}

TEnumAsByte<EObstacleState> AObstacleBase::SwitchState(EObstacleState State) {
	return IObstacles::SwitchState(State);
}

void AObstacleBase::ObstacleEvent()
{
	 IObstacles::ObstacleEvent();
}

