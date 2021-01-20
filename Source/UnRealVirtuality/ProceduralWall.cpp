// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralWall.h"
#include "UObject/Object.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Transform.h"
#include "Math/Quat.h"
#include "Math/TransformVectorized.h"
#include "Components/SceneComponent.h"
#include "Actor.h"

	/** Move an existing point to a new location */
	//UFUNCTION(BlueprintCallable, Category = Spline)
	//void SetLocationAtSplinePoint(int32 PointIndex, const FVector& InLocation, ESplineCoordinateSpace::Type CoordinateSpace, bool bUpdateSpline = true);

using namespace ESplineMeshAxis;
// Sets default values
AProceduralWall::AProceduralWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_MeshInstances = UObject::CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("MeshInstances"), false);

	_SplinePath =  UObject::CreateDefaultSubobject<USplineComponent>(FName("SplinePath"),false);

    _ForwardAxis = ESplineMeshAxis::Type::X;

	_SplinePath->bInputSplinePointsToConstructionScript= true;

	RootComponent = _MeshInstances;

}

void AProceduralWall::OnConstruction(const FTransform& Transform)
{

	_SplinePath->SetLocationAtSplinePoint(1,Transform.InverseTransformPosition(Transform.GetLocation()) + FVector(6000,0,0), ESplineCoordinateSpace::Type::World, true);

	while ( _Offset < _SplinePath->GetSplineLength() ) 
	{

			PlaceMesh(_Offset);
			_Offset = (_Offset + _IncrementalOffset);
	}

	Super::OnConstruction(Transform);

}

void AProceduralWall::PlaceMesh(float Distance) 
{
		//FTransform TSpawnPoint;
		FTransform TempTM;
		FVector SpawnLocation;
		FRotator RRotation;
		FVector VScale(1,1,1);

		//SpawnLocation = _SplinePath->GetLocationAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::Type::World);
		//RRotation = _SplinePath->GetRotationAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::Type::World);

		FTransform TSpawnPoint =_SplinePath->GetTransformAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::Type::World);


	//	UKismetMathLibrary::BreakTransform(TempTM, VTranslation, RRotation, VScale);
		//TSpawnPoint.SetLocation(SpawnLocation);
		//TSpawnPoint.SetScale3D(VScale);
		//TSpawnPoint.SetRotation(FQuat(RRotation));
		_MeshInstances->AddInstance(TSpawnPoint);
}

// Called when the game starts or when spawned
void AProceduralWall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProceduralWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

