// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DragonPawn.h"


void ADragonAIController::BeginPlay()
{
    Super::BeginPlay();

    DragonPawn = (ADragonPawn*)GetPawn();

    if ( Bt != nullptr ) 
    {
        
        //DragonPawn->IsIdle = false;
        RunBehaviorTree(Bt);
        GetBlackboardComponent()->SetValueAsVector(TEXT("NextNavPoint"), NextNavPoint);
        SetFocalPoint(NextNavPoint);
    }
}
