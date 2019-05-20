#pragma once

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

	//TODO-�޸�Ϊ�԰�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTask* LeadingTask;

	//�������п�ʼʱ��(��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StartingTime;

	//��ǰ����ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentTaskID;

};