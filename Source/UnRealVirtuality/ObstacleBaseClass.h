// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacles.h"
#include "ObstacleBaseClass.generated.h"

class AActor;


UCLASS(BlueprintType, Category="Obstacles")
class UNREALVIRTUALITY_API AObstacleBaseClass : public AActor, public IObstacles
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleBaseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	TEnumAsByte<EObstacleState> EState = EObstacleState::Spawning;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	TEnumAsByte<EObstacleType> EType = EObstacleType::Cloud_White;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	bool bFollowingActor = false;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	float MinMarginFwdAndBwd = 0;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	float MinMarginAboveAndBelow = 0;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	float MinMarginLeftAndRight = 0;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	bool bAffectedByWind = false;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	float fScore = 0;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	bool bPlayerDetected = false;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	FVector vMargins = FVector(0);

	UPROPERTY(EditAnywhere,Category="Obstacles")
	AActor* TargetActor;

	UPROPERTY(EditAnywhere,Category="Obstacles")
	FVector TargetLocation;

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
