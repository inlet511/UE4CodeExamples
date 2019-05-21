#pragma once

#include "Sound/SoundCue.h"
#include "TaskSequence.generated.h"

class UTask;

UCLASS()
class CONTIGENCYPLAN_API UTaskSequence :public UObject
{
	GENERATED_BODY()

public:

	//任务序列名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TaskSequenceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* DescriptionAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DescriptionText;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTask* LeadingTask;

	//任务序列开始时间(秒)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartingTime;

	//当前任务ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentTaskID;

};