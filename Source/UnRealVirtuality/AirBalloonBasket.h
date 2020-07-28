// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirBalloonBasket.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNREALVIRTUALITY_API AAirBalloonBasket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAirBalloonBasket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	private: 

	UStaticMeshComponent* Basket = nullptr;
	
	UStaticMeshComponent* Balloon = nullptr;

	UPROPERTY(EditAnywhere)
	bool bAutoMoveForward = false;

	
	UPROPERTY(EditAnywhere)
	float ForwardVelocity = 10000000.0;

	UPROPERTY(EditAnywhere)
	float UpwardBaseVelocity = 1000000.0;

};
