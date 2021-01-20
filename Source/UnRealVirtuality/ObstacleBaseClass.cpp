// Fill out your copyright notice in the Description page of Project Settings.
#include "ObstacleBaseClass.h"
#include "Actor.h"
// Sets default values
AObstacleBaseClass::AObstacleBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacleBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AObstacleBaseClass::IsAffectedByWind() {

	return bAffectedByWind;

}

float AObstacleBaseClass::GetScoreValue() {
	return fScore;
}

TEnumAsByte<EObstacleState> AObstacleBaseClass::GetObstacleState() {
	return EState;
}

TEnumAsByte<EObstacleType> AObstacleBaseClass::GetObstacleType() {
	return EType;
}

float AObstacleBaseClass::LosRange(FVector Direction) {

	return 0;
}

FVector AObstacleBaseClass::GetMargins() {
	
	return vMargins;
}

bool AObstacleBaseClass::PlayerDetected() {

	return bPlayerDetected;

}

TEnumAsByte<EObstacleState> AObstacleBaseClass::SwitchState(EObstacleState State) {

	if ( State != EState ) {

		EState = State;
	}

	return EState;

}

void AObstacleBaseClass::ObstacleEvent() {


}

