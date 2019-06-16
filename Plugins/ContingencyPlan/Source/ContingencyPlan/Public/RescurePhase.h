#pragma once

#include "RescurePhase.generated.h"

class UTaskSequence;


UCLASS(BlueprintType)
class CONTINGENCYPLAN_API URescurePhase :public UObject
{
	GENERATED_BODY()

public:

	//阶段目标
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContingencyPlan" ,meta = (DisplayName = "阶段目标", ToolTip = "当前救援阶段的目标描述"))
    FString PhaseTarget;

    //人力资源统计
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContingencyPlan" ,meta = (DisplayName = "人力统计", ToolTip = "当前救援阶段所需要的工种和人数"))
    FString HRStatistics;

    //任务序列
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ContingencyPlan" ,meta = (DisplayName = "任务序列", ToolTip = "当前救援阶段包含的所有任务序列，数组形式"))
    TArray<UTaskSequence*> TaskSequence;

};