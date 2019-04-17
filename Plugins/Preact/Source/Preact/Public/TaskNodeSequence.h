// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskNode.h"

/**
 * 
 */
class PREACT_API TaskNodeSequence
{
public:
	TaskNodeSequence();
	~TaskNodeSequence();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSharedPtr<class TaskNode> StartingTaskNode;

};
