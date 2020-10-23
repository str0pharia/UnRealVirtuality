// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Clear.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Clear::UBTTask_Clear() 
{

    NodeName = TEXT("Clear Value");

}


 EBTNodeResult::Type UBTTask_Clear::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
 {

     Super::ExecuteTask(OwnerComp,NodeMemory);

     OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

     return EBTNodeResult::Succeeded;
 }