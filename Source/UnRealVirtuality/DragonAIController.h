// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DragonAIController.generated.h"

class UBehaviorTree;
class ADragonPawn;

/**
 * 
 */


UENUM(BlueprintType)
enum EDragonAIState 
{
	IDLE_WAIT		UMETA(DisplayName = "Idle"),
	CHASE			UMETA(DisplayName = "Chase"),
	FOLLOW_PATH		UMETA(DisplayName = "Follow Path"),
	ATTACK			UMETA(DisplayName = "Attack"),
	ATTACK_MOVE		UMETA(DisplayName = "Attack Move"),
	RAGDOLL			UMETA(DisplayName = "Ragdoll"),
	DEFEND			UMETA(DisplayName = "Defend"),
	FROZEN			UMETA(DisplayName = "Frozen"),
	LAND			UMETA(DisplayName = "Land"),
	TAKE_OFF		UMETA(DisplayName = "Take Off")
};

UCLASS()
class UNREALVIRTUALITY_API ADragonAIController : public AAIController
{
	GENERATED_BODY()


	protected:

		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

		ADragonPawn* DragonPawn = nullptr;

		UPROPERTY(VisibleAnywhere)
		TEnumAsByte<EDragonAIState> AIState = EDragonAIState::IDLE_WAIT;

	private:

		UPROPERTY(EditAnywhere)
		UBehaviorTree* Bt;

		UPROPERTY(EditAnywhere)
		FVector NextNavPoint; 

		UPROPERTY(EditAnywhere)
		APawn* PlayerPawn = nullptr;


	
};
