// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EVerticalHandPos:uint8
{
	AboveShoulder,
	WaistToShoulder,
	KneeToWaist,
	BelowKnee
};

UENUM()
enum class EHorizontalHandPos:uint8
{
	Near,
	Mid,
	Extended
};

UENUM()
enum class EFrequency:uint8
{
	Minimum,// 1 lift every 2-5 minutes
	Low,    // 1 lift every minute
	Medium, // 2-3 lifts every minute
	High,   // 4-5 lifts every minute
	VeryHigh,// 6-7 lifts every minute
	Extra,	// 8-9 lifts every minute
	Maximum // 10+

};

UENUM()
enum class EDuration:uint8
{
	Short,  // 1 hour or less
	Medium, // 1 or 2 hours
	Long    // 2 hours or more
};

UENUM()
enum class ETwist :uint8
{
	Minor, // Less than 45 degrees
	Major  // 45 degrees or greater
};


/**
 * 
 */
class ERGONOMICSCORE_API WISHA
{
public:
	WISHA();
	~WISHA();

	float ActuralWeight;
	float UnadjustedWeightLimit;
	float AdjustedWeightLimit;
	float LimitReductionModifier;
	float WeightLimit;
	float RI;

	EVerticalHandPos CurrentVerticalHandPos;
	EHorizontalHandPos CurrentHorizontalHandPos;
	EFrequency CurrentFrequency;
	EDuration CurrentDuration;
	ETwist CurrentTwist;
	
	void Evaluate();
};
