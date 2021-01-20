// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "ProceduralWall.generated.h"

class FObjectInitializer;
class USplineComponent;
class UInstancedStaticMeshComponent;

using namespace ESplineMeshAxis;

UCLASS()
class UNREALVIRTUALITY_API AProceduralWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralWall();
	 
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Procedural Mesh - Instances")
	UInstancedStaticMeshComponent* _MeshInstances;
   
    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Procedural Mesh - Spline Path")
	USplineComponent* _SplinePath;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Procedural Mesh - Spline Forward Axis")
    TEnumAsByte<ESplineMeshAxis::Type> _ForwardAxis;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Procedural Mesh - Offset Next Instance By Distance ")
	float _Offset = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Procedural Mesh - Incremental Offset Per Instance ")
	float _IncrementalOffset = 125.0f;


protected:
	// Called when the game starts or when spawned

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

  	virtual void OnConstruction(const FTransform& Transform) override;


	UFUNCTION(BlueprintCallable, Category = "Prodedural Mesh")
	void PlaceMesh(float Distance);



};
