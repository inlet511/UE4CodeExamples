#pragma once

#include "RescurePhase.generated.h"

class UTaskSequence;


UCLASS()
class CONTIGENCYPLAN_API URescurePhase :public UObject
{
	GENERATED_BODY()

public:

	//�׶�Ŀ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PhaseTarget;

	//������Դͳ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HRStatistics;

	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTaskSequence* TaskSequence;

};