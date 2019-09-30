// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "uni_projectCharacter.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"



AChasingAIController::AChasingAIController(){
 
    // creating the component
    perceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SightPerceptionComponent"));
    
    //creating the sight sense and define affiliation
    sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));
    sightConfig->DetectionByAffiliation.bDetectEnemies = true;
    sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    sightConfig->SightRadius = 850.0f;
    sightConfig->LoseSightRadius = 850.0f+50;
    //assign the sense to the preception
    perceptionComp->ConfigureSense(*sightConfig);
    perceptionComp->SetDominantSense(*sightConfig->GetSenseImplementation());
    //perceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AChasingAIController::OnTargetPerceptionUpdate);

    perceptionComp2 = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("HearingPerceptionComponent"));

    //creating the hearing sense
    hearConfig  = CreateDefaultSubobject<UAISenseConfig_Hearing>(FName("Hear Config"));
    hearConfig->DetectionByAffiliation.bDetectEnemies = true;
    hearConfig->DetectionByAffiliation.bDetectNeutrals = true;
    hearConfig->DetectionByAffiliation.bDetectFriendlies = true;
    hearConfig->HearingRange = 1200.f;
    hearConfig->LoSHearingRange = 1200.f+50;
    
    perceptionComp2->ConfigureSense(*hearConfig);
    perceptionComp2->SetDominantSense(*hearConfig->GetSenseImplementation());
    perceptionComp2->OnTargetPerceptionUpdated.AddDynamic(this, &AChasingAIController::OnTargetPerceptionUpdate);
}

// this is the function that will invoked when player encountered
void AChasingAIController::OnTargetPerceptionUpdate(AActor* actor, FAIStimulus stimulus){
    
    if(Cast <ATP_ThirdPersonCharacter>(actor)){
        lastKnownPlayerPosition = stimulus.StimulusLocation;
        bcanSeePlayer = stimulus.WasSuccessfullySensed();
        
    }

    
}

void AChasingAIController::OnPossess(APawn *inPawn){
    
    Super::OnPossess(inPawn);
    if(behaviorTree != nullptr){
        RunBehaviorTree(behaviorTree);
    }
}
