// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_UpdateChasing.h"
#include "ChasingAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_UpdateChasing::UBTS_UpdateChasing(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
    bNotifyBecomeRelevant = true;
    bNotifyCeaseRelevant = false;
    
}

void UBTS_UpdateChasing::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UE_LOG(LogTemp, Warning, TEXT("become relevant  "));

    // get blackboardComponent and check if it's not empty
    UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
    if(blackboardComp == NULL)
    {
        UE_LOG(LogTemp, Warning, TEXT("FAILED AT on becaome relevant  balckboard "));

        return;
    }
    
    if(!playerKey.IsSet()){
    // retrive players and update the blackboard
    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),PlayerClass, foundActors);
 
    //assuming there's only one player in the game
    
    if(foundActors[0])
    {
        UE_LOG(LogTemp, Warning, TEXT("FOUND PLAYER"));
        blackboardComp->SetValueAsObject(playerKey.SelectedKeyName, foundActors[0]);
      
        }
    }
}

void UBTS_UpdateChasing::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float deltaSeconds){
    UE_LOG(LogTemp, Warning, TEXT("TickNode started "));

    // get the blackboard component and check if it is empty
    UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
 
    if(blackboardComp == NULL){
          UE_LOG(LogTemp, Warning, TEXT("FAILED AT getting balckboard "));
        return;
    }
    // get the AI controller to check validity
    AAIController* aiController  = OwnerComp.GetAIOwner();
    
    if(!aiController){
          UE_LOG(LogTemp, Warning, TEXT("FAILED AT get owner ai "));
        return;
    }
    // now we have the ai controller so we will want to cast it to our AI (ChasingAIController)
    AChasingAIController* chasingAI  = Cast <AChasingAIController> (aiController);
    
    if(!chasingAI){
         UE_LOG(LogTemp, Warning, TEXT("FAILED AT CHASING AI "));
        return;
    }
    // update the current value of canSeePlayer from chasingAi
    
    //UE_LOG(LogTemp,Warning,TEXT("can see? Bool is %s"), (chasingAI->bcanSeePlayer ? TEXT("True") : TEXT("False")));
    blackboardComp->SetValueAsBool(canSeePlayerKey.SelectedKeyName,chasingAI->bcanSeePlayer);
   // blackboardComp->SetValueAsVector(lastKnownPositionVectorKey.SelectedKeyName,chasingAI->lastKnownPlayerPosition);

    // update the last known position
    if(chasingAI->bcanSeePlayer != lastCanSeePlayer ){
        UE_LOG(LogTemp, Warning, TEXT(" last known position changed"));
        blackboardComp->SetValueAsVector(lastKnownPositionKey.SelectedKeyName, chasingAI->lastKnownPlayerPosition);
        
    }
    lastCanSeePlayer = chasingAI->bcanSeePlayer;

    Super::TickNode(OwnerComp, NodeMemory, deltaSeconds);
    
}


FString UBTS_UpdateChasing::GetStaticDescription() const {
    
    return FString::Printf(TEXT("%s: '%s'"), TEXT("Player Class"), PlayerClass ? *PlayerClass->GetName() : TEXT(""))
    .Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("PlayerKey"), playerKey.IsSet() ? *playerKey.SelectedKeyName.ToString() : TEXT("")))
    .Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("LastKnownPositionKey"), lastKnownPositionKey.IsSet() ? *lastKnownPositionKey.SelectedKeyName.ToString() : TEXT("")))
    .Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("CanSeePlayerKey"), canSeePlayerKey.IsSet() ? *canSeePlayerKey.SelectedKeyName.ToString() : TEXT("")));
}
