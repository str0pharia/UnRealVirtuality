// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tiles.generated.h"


enum EObstacleType;
class IObstacles;
class AActor;

UENUM(BlueprintType)
enum ETileTag
{
	Foggy			UMETA(DisplayName = "Foggy"),	
	Foggier			UMETA(DisplayName = "Foggier"),	
	Foggiest		UMETA(DisplayName = "Foggiest"),	
	Wind			UMETA(DisplayName = "Wind"),
	Storm			UMETA(DisplayName = "Storm"),
	Hurricane		UMETA(DisplayName = "Hurricane"),
	Tornado			UMETA(DisplayName = "Tornado"),
	LightRain		UMETA(DisplayName = "Light Rain"),
	HeavyRain		UMETA(DisplayName = "Heavy Rain"),
	LightSnow		UMETA(DisplayName = "Light Snowfall"),
	HeavySnow		UMETA(DisplayName = "Heavy Snow"),
	Dusty			UMETA(DisplayName = "Dusty"),
	Sandstorms		UMETA(DisplayName = "Sandstorms"),
	Swarms			UMETA(DisplayName = "Swarms"),
	Dragon			UMETA(DisplayName = "Dragon"),
	GravityShift	UMETA(DisplayName = "Gravity Shift"),
};

UENUM(BlueprintType)
enum ETileEnvironmentType
{
	Undefined			UMETA(DisplayName = "Undefined"),	
	Plane				UMETA(DisplayName = "Plane"),	
	Forest				UMETA(DisplayName = "Forest"),	
	Desert 				UMETA(DisplayName = "Desert"),	
	Water 				UMETA(DisplayName = "Water"),	
	Sky					UMETA(DisplayName = "Sky"),	
    Winterland			UMETA(DisplayName = "Winterland"),	

};

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UTiles : public UInterface
{
	GENERATED_BODY()

};


class UNREALVIRTUALITY_API ITiles
{
	GENERATED_BODY()


public:
	ITiles() {

	}
	virtual FVector GetAttachPoint() {
		return FVector(0);
	}
	virtual void SpawnObstacle(EObstacleType Type) {

	}
	virtual int GetNumObstacles() {
		return 0;
	}

	virtual TEnumAsByte<EObstacleType> GetRandomObstacleType() {
		return (EObstacleType)0;
	}

	virtual TEnumAsByte<ETileEnvironmentType> GetEnvironmentType() {
		return ETileEnvironmentType::Undefined;
	}

	virtual FTransform GetTileBounds() {
		return FTransform();
	}

};
