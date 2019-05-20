#pragma once

#include "Task.generated.h"

UCLASS()
class CONTIGENCYPLAN_API UTask :public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TaskName;
};