#pragma once
#include "ContingencyPlan.h"
#include "Scenario.generated.h"

UCLASS(BlueprintType)
class CONTINGENCYPLAN_API UScenario :public UObject
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ContingencyPlan" ,meta = (DisplayName = "场景名称"))
    FText ScenarioName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContingencyPlan" ,meta = (DisplayName = "应急预案"))
    UContingencyPlan* ContingencyPlan;
};