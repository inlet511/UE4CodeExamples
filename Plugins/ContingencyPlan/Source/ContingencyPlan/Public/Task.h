#pragma once
#include "WorkerGroup.h"
#include "Sound/SoundCue.h"
#include "Task.generated.h"

UCLASS(BlueprintType)
class CONTINGENCYPLAN_API UTask : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "基本信息", meta = (DisplayName="任务ID"))
	FString TaskID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "基本信息", meta = (DisplayName="任务描述"))
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "基本信息", meta = (DisplayName = "下一任务", ToolTip = "下一个任务"))
	UTask* NextTask;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "基本信息", meta = (DisplayName="前置任务",ToolTip="进行此任务前必须完成的任务，零个或多个"))
	TArray<UTask*> ConditionalTasks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "人力", meta = (DisplayName="负责小组",ToolTip="负责该项任务的小组"))
	TEnumAsByte<WorkerGroup> Worker_Group;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "人力", meta = (DisplayName="人员数量",ToolTip="需要的人数"))
	int32 WorkerCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "任务", meta = (DisplayName="指令语音"))
	USoundCue* OrderAudio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "任务", meta = (DisplayName="指令文字"))
	FString OrderText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "任务", meta = (DisplayName="汇报文字"))
	FString ReportText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "任务", meta = (DisplayName="任务对象", ToolTip = "任务要操作的对象"))
	FString TaskObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "考核", meta = (DisplayName = "开始时间", ToolTip = "单位:秒"))
	FString StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "考核", meta = (DisplayName = "时间限制", ToolTip = "单位:秒"))
	int32 TimeLimit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "考核", meta = (DisplayName = "分值权重", ToolTip = "考核中该节点占总流程的分值的权重"))
	int32 ScoreWeight;

    UPROPERTY(BlueprintReadWrite, Transient, Category = "ContingencyPlan")
    bool bCompleted;
};