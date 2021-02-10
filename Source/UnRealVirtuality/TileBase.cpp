// Fill out your copyright notice in the Description page of Project Settings.

#include "TileBase.h"
#include "Tiles.h"
#include "Actor.h"
#include "Kismet/KismetMathLibrary.h"


// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ATileBase::GetAttachPoint()
{
	return this->AttachPoint;
}

FTransform ATileBase::GetTileBounds() 
{

	FTransform f;

	f.SetLocation(this->TileOrigin);
	f.SetScale3D(this->TileBounds);

	return f;

}
void ATileBase::SpawnObstacle(EObstacleType Type)
{
	UKismetMathLibrary::RandomPointInBoundingBox(SpawnableArea.Origin,SpawnableArea.BoxExtent);
}

int ATileBase::GetNumObstacles()
{
	return this->Obstacles.Num(); 
}

TEnumAsByte<EObstacleType> ATileBase::GetRandomObstacleType()
{
	int32 t = UKismetMathLibrary::RandomIntegerInRange(0,4);
	EObstacleType o = (EObstacleType)t;
	return o;
}


TEnumAsByte<ETileEnvironmentType> ATileBase::GetEnvironmentType()
{
	return this->EnvironmentType;
}