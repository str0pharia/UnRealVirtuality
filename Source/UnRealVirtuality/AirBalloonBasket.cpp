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

	((UStaticMeshComponent*)GetRootComponent())->AddForce(GetActorUpVector() * UpwardBaseVelocity);

	if ( bAutoMoveForward ) {
		((UStaticMeshComponent*)GetRootComponent())->AddForce(GetActorForwardVector() * ForwardVelocity);

		if ( Basket != nullptr ) {
			Basket->AddForce(Basket->GetForwardVector() * ForwardVelocity);
		}

	}
}

void AAirBalloonBasket::throttle(float axis) {

	if ( axis <= 0 )
		return;

	((UStaticMeshComponent*)GetRootComponent())->AddForce(GetActorUpVector() * (ThrottleMaxVelocity * axis));

	
}

void AAirBalloonBasket::turn(FVector direction, float force) {

	((UStaticMeshComponent*)GetRootComponent())->AddForce(direction * force);
	
}

