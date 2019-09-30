// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_findRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"




EBTNodeResult::Type UBTT_findRandomLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
    //Get Blackboard Component
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    // first we need to check if the blackboard comp is not empty
    // if it is return null
    if (BlackboardComp == NULL)
    {
        return EBTNodeResult::Failed;
    }
    APawn* controlledPawn = OwnerComp.GetAIOwner()->GetPawn(); // pawn pointer
    if(controlledPawn == NULL){
        return EBTNodeResult::Failed;
    }
    //get navigation class
    UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if(navSys == NULL){
        return EBTNodeResult::Failed;
    }
    // query parameters where we will go & current location
    FNavLocation result;
    FVector origin = controlledPawn->GetActorLocation();
    
    // now the actual query
    bool success = navSys->GetRandomReachablePointInRadius(origin, radius, result);
    
    if(!success){
        EBTNodeResult:: Failed;
    }
    // id we secceded then we need to store the value in the blackboard and report success
    BlackboardComp->SetValueAsVector(destinationVector.SelectedKeyName, result.Location);
   return EBTNodeResult::Succeeded;
}


FString UBTT_findRandomLocation::GetStaticDescription() const
{
    
    return FString::Printf(TEXT("%s: '%s'"), TEXT("DestinationKey"),  destinationVector.IsSet() ? *destinationVector.SelectedKeyName.ToString() : TEXT(""))
    .Append(FString::Printf(TEXT("\n%s: '%s'"), TEXT("Radius"), *FString::SanitizeFloat(radius)));
}

