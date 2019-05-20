#pragma once

#include "TaskSequence.generated.h"
#include "Templates/SharedPointer.h"

class Task;

UCLASS()
class CONTIGENCYPLAN_API UTaskSequence :public UObject
{
	GENERATED_BODY()

public:

	//������������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TaskSequenceName;

	//TODO-�޸�Ϊ�԰�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSharedPtr<Task> LeadingTask;

	//�������п�ʼʱ��(��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartingTime;

	//��ǰ����ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentTaskID;

};