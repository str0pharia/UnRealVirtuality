// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "DragonPawn.generated.h"


class USkeletalMeshComponent;
class UFloatingPawnMovementComponent;
class UNavMovementComponent;
UENUM(BlueprintType)
enum EDragonAIState 
{
	IDLE_WAIT		UMETA(DisplayName = "Idle"),
	MOVE			UMETA(DisplayName = "Move"),
	ATTACK_LOCK		UMETA(DisplayName = "Attack"),
	ATTACK_MOVE		UMETA(DisplayName = "Attack Move"),
	RAGDOLL			UMETA(DisplayName = "Ragdoll"),
	DEFEND			UMETA(DisplayName = "Defend"),
	AVOID			UMETA(DisplayName = "Avoid"),
	ATTACHED		UMETA(DisplayName = "Attached")
};

static float Z_THRESHOLD = 200.f;	
static float TRACE_DISTANCE = 400.f;



UCLASS()
class UNREALVIRTUALITY_API ADragonPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ADragonPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EDragonAIState> AIState = EDragonAIState::IDLE_WAIT;
	
	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EDragonAIState> PrevAIState;

	void Update(float DeltaTime);

	bool TransitionToState(EDragonAIState s);

	UFUNCTION(BlueprintCallable)
	float DistanceToGround();

	USkeletalMeshComponent *DragonMesh = nullptr;

	UFloatingPawnMovementComponent *PawnMove = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float axis);

	void MoveForward(float axis);

	void LookUpRate(float axis);

	UPROPERTY(BlueprintReadOnly, Category = "AI");
	float RotationRate;	

	UPROPERTY(BlueprintReadOnly);
	bool IsIdle;

	UPROPERTY(BlueprintReadOnly);
	bool OnGround;

	UPROPERTY(BlueprintReadOnly);
	bool Land;

	UPROPERTY(BlueprintReadOnly);
	bool TakeOff;

	UFUNCTION()
	EDragonAIState GetAIState();

	UFUNCTION()
	EDragonAIState SetAIState(EDragonAIState s);

	UFUNCTION(BlueprintCallable)
	void OnMovementModeChanged(bool walk);
};
