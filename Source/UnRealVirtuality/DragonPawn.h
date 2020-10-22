// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DragonPawn.generated.h"

UCLASS()
class UNREALVIRTUALITY_API ADragonPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADragonPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float axis);

	void MoveForward(float axis);

	void LookUpRate(float axis);

	UPROPERTY(BlueprintReadOnly, Category = "");
	float RotationRate;

	UPROPERTY(BlueprintReadOnly);
	bool IsIdle;

	UPROPERTY(BlueprintReadOnly);
	bool OnGround;

	UPROPERTY(BlueprintReadOnly);
	bool Land;

	UPROPERTY(BlueprintReadOnly);
	bool TakeOff;
};
