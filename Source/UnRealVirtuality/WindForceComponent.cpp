// Fill out your copyright notice in the Description page of Project Settings.


#include "WindForceComponent.h"
#include "AirBalloonBasket.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
// Sets default values for this component's properties
UWindForceComponent::UWindForceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}


// Called when the game starts
void UWindForceComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AActor> ActorItr(GetWorld(), AAirBalloonBasket::StaticClass()); ActorItr; ++ActorItr)
	{
         // do stuff

		
		
			 PlayerBalloon = Cast<AAirBalloonBasket>(*ActorItr);

			 	// ...
			UStaticMeshComponent* m = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

			if ( m != nullptr ) {
				OwningActorMesh = m;
			}

	}

}


// Called every frame
void UWindForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (  PlayerBalloon != nullptr && OwningActorMesh != nullptr )  
	{

		//OwningActorMesh->AddForce(PlayerBalloon->WindDirection * (PlayerBalloon->WindStrength * PlayerBalloon->WindSpeed));

		PlayerBalloon->Balloon->AddForce(PlayerBalloon->WindDirection * (PlayerBalloon->WindStrength * PlayerBalloon->WindSpeed));

	}

	// ...
}

