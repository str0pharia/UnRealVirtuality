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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool bAutoMoveForward = false;

	UPROPERTY(EditAnywhere)
	float ThrottleForceScalar = 10000000.0;

	UPROPERTY(EditAnywhere)
	float UpwardBaseForceScalar =20000000.0;

	UPROPERTY(EditAnywhere)
	float ForwardBaseForceScalar = 1000000.0;

	UPROPERTY(EditAnywhere,BlueprintReadOnly , Category = "Wind")
	float WindStrength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wind")
	float WindSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Wind")
	FVector WindDirection;

	TArray<FVector> WindDirectionVectors; 

	UStaticMeshComponent* Basket = nullptr;
	
	UStaticMeshComponent* Balloon = nullptr;

	FTimerHandle UpdateWindTimer;

	void UpdateWind();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;






};
