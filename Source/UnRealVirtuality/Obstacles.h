// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Obstacles.generated.h"

UENUM(BlueprintType)
enum EObstacleState
{
	Spawning					UMETA(DisplayName = "Spawning"),	
	Normal						UMETA(DisplayName = "Normal"),	
	Special						UMETA(DisplayName = "Executing special function/logic"),	
	Disabled					UMETA(DisplayName = "Disabled"),
	InterceptTarget				UMETA(DisplayName = "Intercept Target Actor"),
	MoveToTarget				UMETA(DisplayName = "Move to target Location"),
	Wait						UMETA(DisplayName = "Wait/Idle"),
};

UENUM(BlueprintType)
enum EObstacleClass
{
	Static						UMETA(DisplayName = "Static"),	
	Turret_Static				UMETA(DisplayName = "Static"),	
	Dynamic						UMETA(DisplayName = "Dynamic"),	
	Turret_Dynamic				UMETA(DisplayName = "SplineMovement"),

};

UENUM(BlueprintType)
enum EObstacleType
{
	Cloud_White		= 0			UMETA(DisplayName = "Cloud White"),	
	Cloud_Orange	= 1			UMETA(DisplayName = "Cloud Orange"),
	Red_Balloon		= 2			UMETA(DisplayName = "Red Balloon"),	
	Log				= 3			UMETA(DisplayName = "Log"),	
	WindMill	 	= 4			UMETA(DisplayName = "WindMill"),

};

class AActor;

UINTERFACE(Blueprintable)
class UObstacles : public UInterface
{
	GENERATED_BODY()
};

class UNREALVIRTUALITY_API IObstacles
{
	GENERATED_BODY()
	
	TEnumAsByte<EObstacleState> EState;

	TEnumAsByte<EObstacleType> EType;

	bool bFollowingActor;

	float MinMarginFwdAndBwd;

	float MinMarginAboveAndBelow;

	float MinMarginLeftAndRight;

	bool bAffectedByWind;

	float fScore;

	bool bPlayerDetected;

	FVector vMargins;

	AActor* TargetActor;

	FVector TargetLocation;

public:
	IObstacles() {

	}

	virtual bool IsAffectedByWind() 
	{ 
		return false; 
	}

	virtual float GetScoreValue() 
	{ 
		return 0; 
	}

	virtual TEnumAsByte<EObstacleState>  GetObstacleState() 
	{ 
		return EObstacleState::Spawning; 
	}

	virtual TEnumAsByte<EObstacleType>  GetObstacleType() 
	{ 
		return EObstacleType::Log; 
	}

	virtual float LosRange(FVector Direction)
	{ 
		return 0;
	}

	virtual FVector GetMargins()
	{ 
		return FVector(0);
	}

	virtual bool PlayerDetected() 
	{ 
		return false;
	}

	virtual TEnumAsByte<EObstacleState> SwitchState(EObstacleState State) 
	{ 
		return EObstacleState::Spawning; 
	}

	virtual void ObstacleEvent() 
	{

	}

};
