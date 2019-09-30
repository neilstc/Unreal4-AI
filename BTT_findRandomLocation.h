// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_findRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class UNI_PROJECT_API UBTT_findRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, Category = Blackboard)
    FBlackboardKeySelector destinationVector; // vector of our destination
	
    UPROPERTY(EditAnywhere, Category = parameters)
    float radius = 300.f; //radius as a peremeter
  
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* NodeMemory) override;
    virtual FString GetStaticDescription() const override;
};
