// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CheckBoolVariables.h"
#include "BehaviorTree/BlackboardComponent.h"

/* assuming we have a boolean variable stored, this
 funnction will check the visablity of the "enemy"
 */
bool UBTD_CheckBoolVariables::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
    //Get BlackboardComponent
    const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == NULL)
    {
        return false;
    }
    
    //Perform Boolean Variable Check
    return BlackboardComp->GetValueAsBool(boolVariablesToCheck.SelectedKeyName);

}

FString UBTD_CheckBoolVariables::GetStaticDescription() const
{
    return FString::Printf(TEXT("%s: '%s'"), TEXT("Bool Variable to Check"), boolVariablesToCheck.IsSet() ? *boolVariablesToCheck.SelectedKeyName.ToString() : TEXT(""));
}
