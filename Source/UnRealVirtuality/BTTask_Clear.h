// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Clear.generated.h"

/**
 * 
 */
UCLASS()
class UNREALVIRTUALITY_API UBTTask_Clear : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_Clear();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	
};
