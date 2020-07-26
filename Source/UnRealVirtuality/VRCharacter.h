// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"
class UCameraComponent;
class USceneComponent;
class UStaticMeshComponent;
class UMotionControllerComponent;
class UCurveFloat;
class USplineComponent;
class AHandController;

UCLASS()
class UNREALVIRTUALITY_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere)
 	UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere)
 	USceneComponent* VRRoot = nullptr;

	UPROPERTY(VisibleAnywhere)
 	USplineComponent* TeleportPath = nullptr;

	UPROPERTY(VisibleAnywhere)
 	UStaticMeshComponent* DestinationMarker = nullptr;

	UPROPERTY(VisibleAnywhere)
 	AHandController* LeftController = nullptr;

	UPROPERTY(VisibleAnywhere)
 	AHandController* RightController = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxTeleportDistance = 20.0;

	UPROPERTY(EditAnywhere)
	float TeleportFadeTime = 1.0;

	UPROPERTY(EditAnywhere)
	float TeleportProjectileRadius = 10.0;

	UPROPERTY(EditAnywhere)
	float TeleportProjectileSpeed = 800.0;

	UPROPERTY(EditAnywhere)
	float TeleportSimulationTime = 1.0;

	UPROPERTY(EditAnywhere)
	FVector TeleportProjectionExtent = FVector(100,100,100); 

	bool FindTeleportDestination(TArray<FVector> &OutPath, FVector &OutLocation);

	void UpdateDestinationMarker();

	void UpdateSpline(const TArray<FVector> &Path);

	void BeginTeleport();

	void FinishTeleport();

	UPROPERTY(EditAnywhere)
	UCurveFloat* RadiusVsVelocity;


};
