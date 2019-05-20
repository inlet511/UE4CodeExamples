#pragma once

#include "RescurePhase.generated.h"

UCLASS()
class CONTIGENCYPLAN_API URescurePhase :public UObject
{
	GENERATED_BODY()

public:

	//阶段目标
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PhaseTarget;

	//人力资源统计
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HRStatistics;


};