// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Path.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVIRTUALITY_API UBTTaskNode_Path : public UBTTaskNode
{
	GENERATED_BODY()

	public:

		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
