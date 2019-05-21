#pragma once

#include "Sound/SoundCue.h"
#include "TaskSequence.generated.h"

class UTask;

UCLASS()
class CONTIGENCYPLAN_API UTaskSequence :public UObject
{
	GENERATED_BODY()

public:

	//������������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TaskSequenceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* DescriptionAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DescriptionText;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTask* LeadingTask;

	//�������п�ʼʱ��(��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartingTime;

	//��ǰ����ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentTaskID;

};