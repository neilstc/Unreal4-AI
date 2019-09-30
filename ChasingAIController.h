// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"

#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"


#include "ChasingAIController.generated.h"
 
UCLASS()
class UNI_PROJECT_API AChasingAIController : public AAIController
{
	GENERATED_BODY()
    
    AChasingAIController(); // constructor
    
    UPROPERTY(VisibleDefaultsOnly, Category = AI)
    UAIPerceptionComponent* perceptionComp; // keeping track on preception model
    
    UPROPERTY(VisibleDefaultsOnly, Category = AI)
     UAIPerceptionComponent* perceptionComp2; // keeping track on preception model
    // sight refrence
    UAISenseConfig_Sight* sightConfig;
    //hearing refrence
    UAISenseConfig_Hearing* hearConfig;
   
public:
    FVector lastKnownPlayerPosition;
    bool bcanSeePlayer;
    
    //pointer to  behavior tree so we will run onPossess
    UPROPERTY(EditAnywhere)
    UBehaviorTree* behaviorTree;
    
    virtual void OnPossess(class APawn* inPawn) override;
    
protected:
    UFUNCTION()
    void  OnTargetPerceptionUpdate(AActor* actor, FAIStimulus stimulus);
  
};

