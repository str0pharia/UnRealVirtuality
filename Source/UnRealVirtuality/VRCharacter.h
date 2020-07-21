// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"
class UCameraComponent;
class USceneComponent;
class UStaticMeshComponent;

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
	
	void UpdateDestinationMarker();

	UPROPERTY(VisibleAnywhere)
 	UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere)
 	USceneComponent* VRRoot = nullptr;

	UPROPERTY(VisibleAnywhere)
 	UStaticMeshComponent* DestinationMarker = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxTeleportDistance = 20.0;

	UPROPERTY(EditAnywhere)
	float TeleportFadeTime = 1.0;

	void BeginTeleport();

	void FinishTeleport();


};
