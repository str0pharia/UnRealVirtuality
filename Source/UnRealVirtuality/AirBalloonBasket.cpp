// Fill out your copyright notice in the Description page of Project Settings.


#include "AirBalloonBasket.h"

// Sets default values
AAirBalloonBasket::AAirBalloonBasket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WindDirectionVectors.Add(FVector(0,0,0));
	WindDirectionVectors.Add(FVector(0,0.5f,0));
	WindDirectionVectors.Add(FVector(0,1,0));
	WindDirectionVectors.Add(FVector(-1.0f,0.5f,0));
	WindDirectionVectors.Add(FVector(0,0,0));
	WindDirectionVectors.Add(FVector(-1.0f,-0.5f,0));
	WindDirectionVectors.Add(FVector(0,-1.0f,0));
	WindDirectionVectors.Add(FVector(0,-0.5f,0));

	Basket = (UStaticMeshComponent*)GetDefaultSubobjectByName(TEXT("Basket"));
}

// Called when the game starts or when spawned
void AAirBalloonBasket::BeginPlay()
{
	Super::BeginPlay();

	WindDirection = FVector(0);

	GetWorld()->GetTimerManager().SetTimer(UpdateWindTimer, this, &AAirBalloonBasket::UpdateWind, 20.0f, true);
	
}

void AAirBalloonBasket::UpdateWind() 
{


	int index = FMath::RandRange(0,WindDirectionVectors.Num()-1);

	if ( WindDirectionVectors.IsValidIndex(index) )
	{
		
		WindDirection = WindDirectionVectors[index];

	}

	

}

// Called every frame
void AAirBalloonBasket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
/*
	((UStaticMeshComponent*)GetRootComponent())->AddForce(GetActorUpVector() * UpwardBaseForceScalar);

	if ( bAutoMoveForward ) {

		((UStaticMeshComponent*)GetRootComponent())->AddForce(GetActorForwardVector() * ForwardBaseForceScalar);

	}

*/
}



