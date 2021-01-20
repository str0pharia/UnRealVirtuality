// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Tiles.generated.h"


class IObstacles;
enum EObstacleType;

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

/**
 * 
 */
class UNREALVIRTUALITY_API ITiles
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	FTransform* GetAttachTransform();

	TArray<IObstacles> GetAllObstacles();

	void TileEvent();

	bool TileEventInProgress();

	void SpawnObstacle();

	void SpawnObstacle(EObstacleType Type);

	int GetNumObstacles();

	TEnumAsByte<EObstacleType> GetRandomObstacleType();

	TArray<ETileTag> GetTileTags();

	TEnumAsByte<ETileEnvironmentType> GetEnvironmentType();

};
