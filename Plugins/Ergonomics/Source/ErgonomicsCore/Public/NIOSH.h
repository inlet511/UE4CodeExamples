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


	// Input
	float StartHLocation;
	float EndHLocation;

	float StartVLocation;
	float EndVLocation;

	float StartAsymmetryAngle;
	float EndAsymmetryAngle;

	ECoupling_NIOSH Coupling;

	float Frequency;

	float ActualLoad;



	EDuration_NIOSH Duration;

	class USkeletalMeshComponent* Skeleton;

	//Multipliers
	float HM, VM, AM, DM, FM, CM;

	// Calculate Multipliers
	float CalcHM(float InH);
	float CalcVM(float InV);
	float CalcDM(float InD);
	float CalcAM(float InA);
	float CalcFM(float InFrequency);
	float CalcCM(ECoupling_NIOSH InCoupling);


	//Output

	float RWL;
	float RI;


	// Middle Vars
	FVector StartHandMiddlePoint;
	FVector EndHandMiddlePoint;
	

	void SnapshotStartPose();
	void SnapshotEndPose();

	// 从骨骼位置计算身体转角
	float CalcAsymmetryAngle();

	void Calculate();

};