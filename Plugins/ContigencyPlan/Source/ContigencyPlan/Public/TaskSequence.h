#pragma once

#include "TaskSequence.generated.h"
#include "Templates/SharedPointer.h"

class Task;

UCLASS()
class CONTIGENCYPLAN_API UTaskSequence :public UObject
{
	GENERATED_BODY()

public:

	//任务序列名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TaskSequenceName;

	//TODO-修改为旁白类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSharedPtr<Task> LeadingTask;

	//任务序列开始时间(秒)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartingTime;

	//当前任务ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentTaskID;

};