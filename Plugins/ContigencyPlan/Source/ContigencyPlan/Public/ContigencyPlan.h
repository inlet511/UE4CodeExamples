#pragma once

#include "ContigencyPlan.generated.h"

UCLASS()
class CONTIGENCYPLAN_API UContigencyPlan :public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlanName;
};