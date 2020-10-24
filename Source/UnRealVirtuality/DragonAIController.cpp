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
    DragonPawn->RotationRate = 80.0f;

    PlayerPawn =UGameplayStatics::GetPlayerPawn(GetWorld(),0);

    if ( Bt != nullptr ) {

        RunBehaviorTree(Bt);
        SetFocalPoint(FVector((4283.061035,-1901.961792,1679.399536)));
        MoveToLocation(FVector((4283.061035,-1901.961792,1679.399536)));

    }


}

void ADragonAIController::Tick(float DeltaTime)
{

    Super::Tick(DeltaTime);
}

