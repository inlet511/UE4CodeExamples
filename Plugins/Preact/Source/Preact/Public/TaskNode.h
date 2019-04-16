// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class TaskForceGroup : uint8
{
	TFG_Machinary UMETA(DisplayName="Machinary"),
	TFG_Construction UMETA(DisplayName="Construction"),
};

/**
 * 
 */
class PREACT_API TaskNode
{
public:
	TaskNode();
	~TaskNode();

	UPROPERTY()
	TEnumAsByte<TaskForceGroup> InChargeGroup;

	UPROPERTY()
	int8 WorkerCount;

	
};
