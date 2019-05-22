#pragma once
#include "ContigencyPlan.generated.h"

#define LOCTEXT_NAMESPACE "ContigencyPlan"

class URescurePhase;

UCLASS(BlueprintType)
class CONTIGENCYPLAN_API UContigencyPlan : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName="预案名称"))
	FText PlanName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (DisplayName="救援阶段"))
	TArray<URescurePhase*> RescurePhases;
};

#undef LOCTEXT_NAMESPACE