#pragma once
#include "WorkerGroup.h"
#include "Task.generated.h"


UCLASS()
class CONTIGENCYPLAN_API UTask : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TaskID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTask* NextTask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTask*> ConditionalTasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<WorkerGroup> Worker_Group;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WorkerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Order;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TaskObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReportText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TimeLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ScoreWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCompleted;
};