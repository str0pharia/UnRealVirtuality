// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tiles.h"
#include "TileBase.generated.h"

enum EObstacleType;

UCLASS(BlueprintType)
class UNREALVIRTUALITY_API ATileBase : public AActor, public ITiles
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;


public:	

	TArray<IObstacles*> Obstacles;

	UPROPERTY(BlueprintReadWrite, Category = "Tile Properties")
	FVector TileBounds;

	UPROPERTY(BlueprintReadWrite, Category = "Tile Properties")
	FVector TileOrigin;

	UPROPERTY(BlueprintReadWrite, Category = "Tile Properties")
	FVector AttachPoint;
	
	UPROPERTY(BlueprintReadWrite, Category = "Tile Properties")
	TEnumAsByte<ETileEnvironmentType> EnvironmentType;
	
	UPROPERTY(BlueprintReadWrite, Category = "Tile Properties")
	FBoxSphereBounds SpawnableArea;

public:	
	// Called every frame
 	void Tick(float DeltaTime) override;
	
	virtual FVector GetAttachPoint();

	virtual void SpawnObstacle(EObstacleType Type);

	virtual int GetNumObstacles();

	virtual FTransform GetTileBounds();

	virtual TEnumAsByte<EObstacleType> GetRandomObstacleType();

	virtual TEnumAsByte<ETileEnvironmentType> GetEnvironmentType(); 


};
