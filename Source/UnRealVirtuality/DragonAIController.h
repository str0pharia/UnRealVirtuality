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
UCLASS()
class UNREALVIRTUALITY_API ADragonAIController : public AAIController
{
	GENERATED_BODY()


	protected:

		virtual void BeginPlay();


		ADragonPawn* DragonPawn;

	private:

		UPROPERTY(EditAnywhere)
		UBehaviorTree* Bt;

		UPROPERTY(EditAnywhere)
		FVector NextNavPoint; 
	
};
