// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles.h"
#include "ObstacleBase.generated.h"

class AActor;

UCLASS(BlueprintType, Category="Obstacles")
class UNREALVIRTUALITY_API AObstacleBase : public AActor, public IObstacles
{
	GENERATED_BODY()
	
public:	
	// Sets default val ues for this actor's properties
	AObstacleBase();

	~AObstacleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool IsAffectedByWind();

	virtual float GetScoreValue();

	virtual TEnumAsByte<EObstacleState> GetObstacleState();

	virtual TEnumAsByte<EObstacleType> GetObstacleType();

	virtual float LosRange(FVector Direction);

	virtual FVector GetMargins();

	virtual bool PlayerDetected();

	virtual TEnumAsByte<EObstacleState>  SwitchState(EObstacleState State);

	virtual void ObstacleEvent();


};
