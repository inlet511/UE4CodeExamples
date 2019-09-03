// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//UENUM()
//enum class ENeckAdjustment
//{
//	SideBending,
//	Twisted
//};
//
//UENUM()
//enum class ETrunkAdjustment
//{
//	Twisted,
//	SideBending
//};
//
//UENUM()
//enum class ELegPos_REBA :uint8
//{
//	Bilateral,	
//	OneLegRaised
//};
//
//UENUM()
//enum class ELegAdjustment :uint8
//{
//	Normal,		//	Straight
//	MinorBend,	//	30 ~ 60
//	MajorBend	//	60+
//};

//UENUM()
//enum class ELoadType_REBA :uint8
//{
//	Minimum,	//	< 11 lbs
//	Medium,		//	11 - 22 lbs
//	Maximum		//	> 22 lbs
//};

//UENUM()
//enum class EWristAdjustment :uint8
//{
//	Normal,
//	BendFromMidline,
//	Twisted
//};

UENUM()
enum class ECoupling_REBA :uint8
{
	Good,
	Fair,
	Poor,
	Unacceptable
};


/**
 * 
 */
class ERGONOMICSCORE_API REBA
{
public:
	REBA();
	~REBA();

	/*
		Neck Position(Front and Back)
		0~20						:	+1
		20+							:	+2
		<0							:	+2
	*/
	float NeckPosition;

	//ENeckAdjustment NeckAdjustment;

	/*
		Trunk Angle(Forward)
		0							:	+1
		-20 ~ 20					:	+2
		20 ~ 60						:	+3
		<-20						:	+3
		60+							:	+4
	*/
	float TrunkPosition;

	//ETrunkAdjustment TrunkAdjustment;

	//ELegPos_REBA LegPos;

	//ELegAdjustment LegAdjustment;

	//ELoadType_REBA LoadType;
	float Load;

	// if there is shock force, rapid buildup of force, or sudden exertion is required.
	bool bShockForce;

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
		-15 ~ 15					:	+1
		15+							:	+2
		<-15						:	+2
	*/
	float WristPostion;

	//EWristAdjustment WristAdjustment;

	ECoupling_REBA Coupling;

	// Are one or more body parts held for longer than one minute (static)?
	bool bActivityScoreA;

	// Are there repeated range actions (more than 4x/minute)?
	bool bActivityScoreB;

	// Is there action that causes large range changes in posture / unstable base?
	bool bActivityScoreC;

	class USkeletalMeshComponent* Skeleton;

	void SnapshotPose();

	// Table A, Neck, Trunk Pose, Legs
	TArray<TArray<TArray<uint16>>> TableA;

	// Table B, UpperArm, LowerArm, Wrist
	TArray<TArray<TArray<uint16>>> TableB;

	TArray<TArray<uint16>> TableC;

	int16 REBAScore;

};