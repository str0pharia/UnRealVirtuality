// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralWall.h"
#include "UObject/Object.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Transform.h"
#include "Math/BoxSphereBounds.h"
#include "Math/Quat.h"
#include "Math/TransformVectorized.h"
#include "Components/SceneComponent.h"
#include "Actor.h"

	/** Move an existing point to a new location */
	//UFUNCTION(BlueprintCallable, Category = Spline)
	//void SetLocationAtSplinePoint(int32 PointIndex, const FVector& InLocation, ESplineCoordinateSpace::Type CoordinateSpace, bool bUpdateSpline = true);
struct FProceduralMeshInfo;

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

			FProceduralMeshInfo NextInstanceData = PlaceMesh(_Offset);

			if ( NextInstanceData.LastElement == nullptr || NextInstanceData.LastElement->Index != NextInstanceData.Index ) {
				return;
			} 
			
			
			if (GetRadius(&NextInstanceData) > 0.0 )
			{
				SetLastInstanceData(&NextInstanceData);
				_Offset = (_Offset + GetNextOffset(&NextInstanceData));
			}

			

			
	}

	Super::OnConstruction(Transform);

}

FProceduralMeshInfo AProceduralWall::PlaceMesh(float Distance) 
{
		int32 Index = -1;
	
		
		float Z_Rotation = FMath::FRandRange(0,180);
		float X_Rotation = FMath::FRandRange(1,10);
		float Y_Rotation = FMath::FRandRange(1,15);
		float Z_Scale= FMath::FRandRange(0.5 , 3);
		float X_Scale= FMath::FRandRange(0.5 , 3);
		float Y_Scale = FMath::FRandRange(0.5 , 3);
		
		
		FVector SpawnAtLocation = _SplinePath->GetLocationAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::Type::World);
		
		
		FRotator SpawnWithRotation = _SplinePath->GetRotationAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::Type::World);

		FVector TransformedDirection = _SplinePath->GetDirectionAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::Type::World);


		FVector SpawnInScale(X_Scale,Y_Scale,Z_Scale);
	//	FTransform TSpawnPoint =_SplinePath->GetTransformAtDistanceAlongSpline(Distance,ESplineCoordinateSpace::Type::World);
		FTransform FinalTransform = FTransform( FQuat(SpawnWithRotation + FRotator(0,0,Z_Rotation) ), (SpawnAtLocation + (TransformedDirection.GetSafeNormal() * Distance) ) , SpawnInScale*SpawnInScale);




	
		//	UKismetMathLibrary::BreakTransform(TempTM, VTranslation, RRotation, VScale);
		//TSpawnPoint.SetLocation(SpawnLocation);
		//TSpawnPoint.SetScale3D(FVector(X_Scale, Y_Scale, Z_Scale));

//FQuat(RRotation


		FProceduralMeshInfo ProceduralMeshInfo;

		FInstancedStaticMeshInstanceData Instance;

		Index = _MeshInstances->AddInstance(FinalTransform);
		if (( _MeshInstances->PerInstanceSMData).IsValidIndex(Index) ) 
		{
			//Instance = _MeshInstances->PerInstanceSMData[Index];

			ProceduralMeshInfo = CreateInstance(Index,FinalTransform,_MeshInstances);

			
			//UStaticMesh* StaticMesh = Instance.StaticMesh;
			//ProceduralMeshInfo->Mesh = StaticMesh;
			//ProceduralMeshInfo->WorldTransform = Instance.Transform;
			//ProceduralMeshInfo->Bounds = Instance.CalcBounds(const ProceduralMeshInfo->WorldTransform); 
			

		} else {
			ProceduralMeshInfo = FProceduralMeshInfo{ -1, FTransform(), FBoxSphereBounds(), nullptr};
		}

		return ProceduralMeshInfo;
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

	FProceduralMeshInfo* AProceduralWall::GetLastInstanceData()
	{
		return LastInstanceData;
	}

	void AProceduralWall::SetLastInstanceData(FProceduralMeshInfo* Instance)
	{
		if ( Instance->Index != -1 )
		{
			SetLastInstanceData(Instance);
		}
	}

	FProceduralMeshInfo AProceduralWall::CreateInstance(int32 Index, FTransform T, UInstancedStaticMeshComponent * MeshInstanceComponent) {

		
		FTransform WorldTransform = T;
		TArray<FInstancedStaticMeshInstanceData> InstanceData = MeshInstanceComponent->PerInstanceSMData;
		if ( InstanceData.IsValidIndex(Index) ) 
		{
			UE_LOG(LogTemp,Warning,TEXT("Failed to create statiic mesh instance, invalid index."));
			return FProceduralMeshInfo{ -1, FTransform(), FBoxSphereBounds(), nullptr};		
		}
		FInstancedStaticMeshInstanceData Data = InstanceData[Index];

		FBoxSphereBounds Bounds = MeshInstanceComponent->CalcBounds(T);
		struct FProceduralMeshInfo Info = FProceduralMeshInfo{ Index, WorldTransform, Bounds, LastInstanceData};
		return Info;
	}

	int32 AProceduralWall::GetIndex(FProceduralMeshInfo* Data) 
	{
		int32 index = (Data != nullptr) ? Data->Index : -1;
		return index;

	} 

	FTransform AProceduralWall::GetTransform(FProceduralMeshInfo* Data) 
	{
		FTransform T = (Data != nullptr) ? Data->WorldTransform : FTransform();
		return T;

	} 

	FBoxSphereBounds AProceduralWall::GetBounds(FProceduralMeshInfo* Data) 
	{
		FBoxSphereBounds B = (Data != nullptr) ? Data->Bounds : FBoxSphereBounds();
		return B;

	} 

	float AProceduralWall::GetRadius(FProceduralMeshInfo* Data) 
	{
		float R = (Data != nullptr && Data->Bounds.SphereRadius > 0 ) ? Data->Bounds.SphereRadius : 0;	
		return R;
	}


	float AProceduralWall::GetNextOffset(FProceduralMeshInfo* Data) {

 		float d = _IncrementalOffset;
		if (Data != nullptr && Data->LastElement != nullptr ) 
		{
		 	d = FVector::Distance(GetTransform(Data->LastElement).GetLocation() + ( GetTransform(Data->LastElement).GetRotation().GetForwardVector() * (GetRadius(Data->LastElement)*0.5f) )  ,GetTransform(Data).GetLocation() + ( GetTransform(Data).GetRotation().GetForwardVector() * (GetRadius(Data)*0.5f) ) );

		}
		return d;
	}
