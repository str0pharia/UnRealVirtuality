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
        SetFocalPoint(FVector(-3816.474121,2243.680664,348.274414));
        MoveToLocation(FVector(-3816.474121,2243.680664,348.274414));

    }


}

void ADragonAIController::Tick(float DeltaTime)
{

    Super::Tick(DeltaTime);
}

