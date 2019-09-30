// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckBoolVariables.generated.h"

/**
 * 
 */
UCLASS()
class UNI_PROJECT_API UBTD_CheckBoolVariables : public UBTDecorator
{
	GENERATED_BODY()
    
protected:
    UPROPERTY(EditAnywhere, Category = BlackBoard)
    FBlackboardKeySelector boolVariablesToCheck;
    
public:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
    virtual FString GetStaticDescription() const override;
    
	
};
