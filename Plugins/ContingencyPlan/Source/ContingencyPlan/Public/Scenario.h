#pragma once
#include "ContingencyPlan.h"
#include "Scenario.generated.h"

UCLASS(BlueprintType)
class CONTINGENCYPLAN_API UScenario :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "场景名称"))
		FText ScenarioName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "应急预案"))
		UContingencyPlan* ContingencyPlan;
};