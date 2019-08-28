// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM()
enum class ECoupling_NIOSH :uint8
{
	Good,
	Fair,
	Poor
};

UENUM()
enum class EFrequency_NIOSH :uint8
{
	Minimum, // <= 0.2
	Low,	// 0.5
	Medium, // 1
	High,	// 2
	Maximum // 3
};

UENUM()
enum class EDuration_NIOSH :uint8
{
	Low, // 1
	Medium, // 1-2
	High // 2-8
};


/**
 * 
 */
class ERGONOMICSCORE_API NIOSH
{
public:
	NIOSH();
	~NIOSH();

	float OriginHLocation;
	float DestHLocation;

	float OrginVLocation;
	float DestVLocation;

	float OriginAsymmetryAngle;
	float DestAsymmetryAngle;

	ECoupling_NIOSH Coupling;

	EFrequency_NIOSH Frequency;

	float AverageLoad;

	float MaximumLoad;

	EDuration_NIOSH Duration;
};