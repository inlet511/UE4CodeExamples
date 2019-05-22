#pragma once

#include "Sound/SoundCue.h"
#include "TaskSequence.generated.h"

class UTask;

UCLASS(BlueprintType)
class CONTIGENCYPLAN_API UTaskSequence :public UObject
{
	GENERATED_BODY()

public:

	//任务序列名称
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString TaskSequenceName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "描述音频"))
	USoundCue* DescriptionAudio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "描述文字"))
	FString DescriptionText;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "起始任务"))
	UTask* LeadingTask;

	//任务序列开始时间(秒)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "开始时间"))
	int32 StartingTime;

	//当前任务ID
	UPROPERTY(BlueprintReadWrite)
	FString CurrentTaskID;

};