// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindForceComponent.generated.h"

class AAirBalloonBasket;
class UStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALVIRTUALITY_API UWindForceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWindForceComponent();

	UPROPERTY(VisibleAnywhere,Category = "Wind")
	AAirBalloonBasket* PlayerBalloon = nullptr;

	UPROPERTY(VisibleAnywhere,Category = "Wind")
	UStaticMeshComponent* OwningActorMesh = nullptr;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:




		
};
