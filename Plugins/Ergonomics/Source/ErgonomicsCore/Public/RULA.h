// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ELoadType_RULA:uint8
{
	Minimum,	// <4.4 lbs	(intermittent)
	Light,		// 4.4 ~ 22 lbs	(intermittent)
	Medium,		// 4.4 ~ 22 lbs	(static or repeated)
	Heavy		// >22 lbs or repeated or shocks
};

//UENUM()
//enum class ELegPos_RULA :uint8
//{
//	Bilateral,	
//	OneLegRaised
//};


/**
 * 
 */
class ERGONOMICSCORE_API RULA
{
public:
	RULA();
	~RULA();

	/*
		- 20 ~ + 20	:	+1
		< -20				:	+2
		+  20 ~ 45			:	+2
		+  45 ~ 90			:	+3
		+  >90				:	+4
	*/
	float UpperArmPosition;

	/* 
		Shoulder is Raised
		True						:	+1
	*/
	bool bShoulderRaised;


	/*
		Upper arm is abducted
		True						:	+1
	*/
	bool bUpperArmAbducted;

	/* 
		Arm is supported or person is leaning
		True						:	+1
	*/
	bool bLeaning;

	/*
		Lower Arm Position
		60~100						:	+1
		0~60						:	+2
		100+						:	+2
	*/
	float LowerArmPosition;

	/*
		Is either arm working across midline or out to side of body?
	*/
	bool bLowerArmAdjustments;

	/*
		0							:	+1
		-15 ~ 15					:	+2
		15+							:	+3
		<-15						:	+3
	*/
	float WristPostion;

	/*
		Wrist bent from midline
		True						:	+1
	*/
	bool bWristAdjustments;

	// If wrist is twisted in mid-range
	bool bWristTwistMidRange;

	// If wrist is at or near end of range
	bool bWristNearEndRange;

	// Select if posture is mainly static (i.e. held > 1 minute), or if action repeated occurs 4X per minute or more.
	bool bWristMuscleUse;

	// wrist load
	ELoadType_RULA WristLoad;

	/*
		Neck Position(Front and Back)
		0~10						:	+1
		10~20						:	+2
		20+							:	+3
		<0							:	+4
	*/
	float NeckPosition;
		
	bool bNeckTwisted;

	bool bNeckSideBending;


	/*
		Trunk Angle(Forward)
		0							:	+1
		0 ~ 20						:	+2
		20 ~ 60						:	+3
		60+							:	+4
	*/
	float TrunkPosition;

	bool bTrunkTwisted;

	bool bTrunkSideBending;

	//ELegPos_RULA LegPos;

	// posture is mainly static (i.e. held > 1 minute), or if action repeated occurs 4X per minute or more.
	bool bTrunkMuscleUse;

	// Neck, Trunk, and Legs
	ELoadType_RULA TrunkLoad;

	class USkeletalMeshComponent* Skeleton;

	
	TArray<TArray<TArray<TArray<uint16>>>> TableA;

	TArray<TArray<TArray<uint16>>> TableB;

	TArray<TArray<uint16>> TableC;

	void SnapshotPose();

};
