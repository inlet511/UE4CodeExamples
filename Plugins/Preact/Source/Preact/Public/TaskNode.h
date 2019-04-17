// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Guid.h"

UENUM(BlueprintType)
enum class WorkerTypeEnum : uint8
{
	WT_Machinary UMETA(DisplayName="Machinary"),
	WT_Construction UMETA(DisplayName="Construction"),
};

/**
 * 
 */
class PREACT_API TaskNode
{
public:
	TaskNode():TaskNodeID(FGuid::NewGuid()){};
	~TaskNode();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="BasicInfo")
	FGuid TaskNodeID;
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="BasicInfo")
	FString Description;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="WorkerType")
	WorkerTypeEnum InChargeWorkerType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="WorkerType")
	int8 WorkerCount;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="TaskInfo")
	FString OrderAudio;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="TaskInfo")
	FString Report;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="TaskInfo")
	float TimeLimit;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="ScoreInfo")
	float ScoreWeight;

private:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="BasicInfo")
	TSharedPtr<TaskNode> NextTaskNode;

public:

	bool operator=(const TaskNode& OtherNode)
	{
		return this->TaskNodeID == OtherNode.TaskNodeID;
	}

	UFUNCTION()
	TSharedPtr<TaskNode> GetNextTaskNode();

	UFUNCTION()
	void SetNextTaskNode(TSharedPtr<TaskNode> Node);

	
};
