// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ELiftLowerPoint :uint8
{
	AboveShoulder,
	KnuckleToShoulder,
	FloorToKnuckle
};

UENUM()
enum class EFrequency_Snook :uint8
{
	Minimum, // 1 action /8 hrs
	Low,	//  1 action /30 minutes
	Medium, //  1 action /5 minutes
	High,	//  1 action / 2 minutes
	Maximum //  1 action /minute
};

UENUM()
enum class EHDistance :uint8
{
	Near, // 7 inches
	Medium, //10 inches
	Far		// 15 inches
};

UENUM()
enum class ELiftDistance :uint8
{
	Near, // 10 inches
	Medium, //20 inches
	Far		// 30 inches
};

/**
 * 
 */
class ERGONOMICSCORE_API Snook
{
public:
	Snook();
	~Snook();

	ELiftLowerPoint LiftLowerPoint;
	EFrequency_Snook Frequency;
	EHDistance Distance;
	ELiftDistance LiftDistance;
	float ActualWeight;
};
