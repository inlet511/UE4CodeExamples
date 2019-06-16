#pragma once
#include "ContingencyPlan.generated.h"

#define LOCTEXT_NAMESPACE "ContingencyPlan"

class URescurePhase;

UCLASS(BlueprintType)
class CONTINGENCYPLAN_API UContingencyPlan : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ContingencyPlan", meta = (DisplayName="预案名称"))
	FText PlanName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RescurePhase" ,meta = (DisplayName = "救援阶段"))
    TArray<URescurePhase*> RescurePhases;
};

#undef LOCTEXT_NAMESPACE