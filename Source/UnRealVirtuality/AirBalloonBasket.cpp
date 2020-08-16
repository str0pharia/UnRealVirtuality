// Fill out your copyright notice in the Description page of Project Settings.


#include "AirBalloonBasket.h"

// Sets default values
AAirBalloonBasket::AAirBalloonBasket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Basket = (UStaticMeshComponent*)GetDefaultSubobjectByName(TEXT("Basket"));
}

// Called when the game starts or when spawned
void AAirBalloonBasket::BeginPlay()
{
	Super::BeginPlay();

	
	
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



