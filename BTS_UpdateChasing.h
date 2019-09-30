// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BTS_UpdateChasing.generated.h"


/**
 * 
 */
UCLASS()
class UNI_PROJECT_API UBTS_UpdateChasing : public UBTService
{
	GENERATED_BODY()
	
    //variables
    //currently see the player or not refrence in blackboard
    UPROPERTY(EditAnywhere, Category = Blackboard)
    FBlackboardKeySelector canSeePlayerKey;
    //player seen blackboard refrence
    UPROPERTY(EditAnywhere, Category = Blackboard)
    FBlackboardKeySelector playerKey;
    // last known place vector
    UPROPERTY(EditAnywhere, Category = Blackboard)
    FBlackboardKeySelector lastKnownPositionKey;
    
    
private:
    //previouse see player state
    bool lastCanSeePlayer;
    UPROPERTY(EditAnywhere, Category = PlayerClass)
    TSubclassOf<AActor> PlayerClass;

protected:
    //functions
    virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float deltaSeconds) override;
    UBTS_UpdateChasing(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());  //constructor
    virtual FString GetStaticDescription() const override;
    
    
    
    
};
