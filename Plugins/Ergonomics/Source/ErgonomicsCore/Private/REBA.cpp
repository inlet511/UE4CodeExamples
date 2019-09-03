// Fill out your copyright notice in the Description page of Project Settings.


#include "REBA.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Editor.h"
#include "TransformVectorized.h"
#include "Plane.h"

REBA::REBA()
{

// Table A
	TArray<TArray<int16>> Neck1,Neck2,Neck3;

	TArray<int16> Trunk11 = { 1,2,3,4 };
	TArray<int16> Trunk12 = { 2,3,4,5 };
	TArray<int16> Trunk13 = { 2,4,5,6 };
	TArray<int16> Trunk14 = { 3,5,6,7 };
	TArray<int16> Trunk15 = { 4,6,7,8 };

	TArray<int16> Trunk21 = { 1,2,3,4 };
	TArray<int16> Trunk22 = { 3,4,5,6 };
	TArray<int16> Trunk23 = { 4,5,6,7 };
	TArray<int16> Trunk24 = { 5,6,7,8 };
	TArray<int16> Trunk25 = { 6,7,8,9 };

	TArray<int16> Trunk31 = { 3,3,5,6 };
	TArray<int16> Trunk32 = { 4,5,6,7 };
	TArray<int16> Trunk33 = { 5,6,7,8 };
	TArray<int16> Trunk34 = { 6,7,8,9 };
	TArray<int16> Trunk35 = { 7,8,9,9 };

	Neck1.Add(Trunk11);
	Neck1.Add(Trunk12);
	Neck1.Add(Trunk13);
	Neck1.Add(Trunk14);
	Neck1.Add(Trunk15);

	Neck2.Add(Trunk21);
	Neck2.Add(Trunk22);
	Neck2.Add(Trunk23);
	Neck2.Add(Trunk24);
	Neck2.Add(Trunk25);

	Neck3.Add(Trunk31);
	Neck3.Add(Trunk32);
	Neck3.Add(Trunk33);
	Neck3.Add(Trunk34);
	Neck3.Add(Trunk35);

	TableA.Add(Neck1);
	TableA.Add(Neck2);
	TableA.Add(Neck3);

//Table B
	TArray<TArray<int16>> UpperArm1, UpperArm2, UpperArm3, UpperArm4, UpperArm5, UpperArm6;


	TArray<int16> LowerArm11 = {1,2,2};
	TArray<int16> LowerArm12 = {1,2,3};
	TArray<int16> LowerArm21 = {1,2,3};
	TArray<int16> LowerArm22 = {2,3,4};
	TArray<int16> LowerArm31 = {3,4,5};
	TArray<int16> LowerArm32 = {4,5,5};
	TArray<int16> LowerArm41 = {4,5,5};
	TArray<int16> LowerArm42 = {5,6,7};
	TArray<int16> LowerArm51 = {6,7,8};
	TArray<int16> LowerArm52 = {7,8,8};
	TArray<int16> LowerArm61 = {7,8,8};
	TArray<int16> LowerArm62 = {8,9,9};
	
	UpperArm1.Add(LowerArm11);
	UpperArm1.Add(LowerArm12);

	UpperArm2.Add(LowerArm21);
	UpperArm2.Add(LowerArm22);

	UpperArm3.Add(LowerArm31);
	UpperArm3.Add(LowerArm32);

	UpperArm4.Add(LowerArm41);
	UpperArm4.Add(LowerArm42);

	UpperArm5.Add(LowerArm51);
	UpperArm5.Add(LowerArm52);

	UpperArm6.Add(LowerArm61);
	UpperArm6.Add(LowerArm62);

	TableB.Add(UpperArm1);
	TableB.Add(UpperArm2);
	TableB.Add(UpperArm3);
	TableB.Add(UpperArm4);
	TableB.Add(UpperArm5);
	TableB.Add(UpperArm6);

//Table C
	TArray<int16> ScoreA1 = {1,1,1,2,3,3,4,5,6,7,7,7};
	TArray<int16> ScoreA2 = {1,2,2,3,4,4,5,6,6,7,7,8};
	TArray<int16> ScoreA3 = {2,3,3,3,4,5,6,7,7,8,8,8};
	TArray<int16> ScoreA4 = {3,4,4,4,5,6,7,8,8,9,9,9};
	TArray<int16> ScoreA5 = {4,4,4,5,6,7,8,8,9,9,9,9};
	TArray<int16> ScoreA6 = {6,6,6,7,8,8,9,9,10,10,10,10};
	TArray<int16> ScoreA7 = {7,7,7,8,9,9,9,10,10,11,11,11};
	TArray<int16> ScoreA8 = {8,8,8,9,10,10,10,10,10,11,11,11};
	TArray<int16> ScoreA9 = {9,9,9,10,10,10,11,11,11,12,12,12};
	TArray<int16> ScoreA10 = {10,10,10,11,11,11,11,12,12,12,12,12};
	TArray<int16> ScoreA11 = {11,11,11,11,12,12,12,12,12,12,12,12};
	TArray<int16> ScoreA12 = {12,12,12,12,12,12,12,12,12,12,12,12};
	
	TableC.Add(ScoreA1);
	TableC.Add(ScoreA2);
	TableC.Add(ScoreA3);
	TableC.Add(ScoreA4);
	TableC.Add(ScoreA5);
	TableC.Add(ScoreA6);
	TableC.Add(ScoreA7);
	TableC.Add(ScoreA8);
	TableC.Add(ScoreA9);
	TableC.Add(ScoreA10);
	TableC.Add(ScoreA11);
	TableC.Add(ScoreA12);

}

REBA::~REBA()
{

}

void REBA::SnapshotPose()
{
	/*************************************
		
		Table A
		Step 1 Locate Neck Position 

	*************************************/

	FTransform NeckTrans = Skeleton->GetSocketTransform(FName(TEXT("head")), ERelativeTransformSpace::RTS_ParentBoneSpace);

	//在head bone 中，parent space中，左右摇头用Roll表示，  左右Bend 用 Pitch 表示， 前后点头用Yaw表示...
	float NeckRotPitch = NeckTrans.GetRotation().Rotator().Pitch;
	float NeckRotYaw = NeckTrans.GetRotation().Rotator().Yaw + 15.3f;
	float NeckRotRoll = NeckTrans.GetRotation().Rotator().Roll;

	/*************************************

		Step 1a Adjust

	*************************************/

	int16 NeckPositionScore = 0;
	if(NeckRotYaw>0 && NeckRotYaw<=20)
		NeckPositionScore+=1;
	else if(NeckRotYaw > 20 || NeckRotYaw<0)
		NeckPositionScore += 2;
	
	if (FMath::Abs(NeckRotRoll) > 5)
		NeckPositionScore += 1;
	if (FMath::Abs(NeckRotPitch) > 5)
		NeckPositionScore += 1;

	NeckPositionScore = FMath::Clamp<int16>(NeckPositionScore, 1, 3);

	/*************************************
		
		Step 2 Locate Trunk Position 
		
	*************************************/

	int16 TrunkPositionScore = 0;
	AActor* BodyActor = Skeleton->GetOwner();
	FVector TrunkDir = (Skeleton->GetSocketLocation(FName(TEXT("neck_01"))) - Skeleton->GetSocketLocation(FName(TEXT("pelvis")))).GetSafeNormal();

	//躯干向量投影到平面上的向量
	FVector TrunkDirProject2Side = FVector::VectorPlaneProject(TrunkDir, BodyActor->GetActorRightVector()).GetSafeNormal();

	FVector BodyUpDir = (BodyActor->GetActorUpVector()).GetSafeNormal();	
	FVector CrossProductResult = FVector::CrossProduct(TrunkDirProject2Side, BodyUpDir);

	float PitchAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TrunkDirProject2Side, BodyUpDir)));
	float PitchSign = FVector::DotProduct(CrossProductResult, BodyActor->GetActorRightVector()) >= 0 ? 1 : -1;

	//根据正常站姿调整,并调整符号
	float Angle_Adjust = -1.0f * (PitchAngle * PitchSign - 4.62f);
	

#if WITH_EDITOR
	UE_LOG(LogTemp, Log, TEXT("Angle_Adjust:%f"),Angle_Adjust);
	FVector HeadLoc = Skeleton->GetSocketLocation(FName(TEXT("head")));
	DrawDebugDirectionalArrow(GEditor->GetEditorWorldContext().World(), HeadLoc, HeadLoc + 100.0f * BodyUpDir, 5, FColor(255,0,0), false, 30.0f);
	DrawDebugDirectionalArrow(GEditor->GetEditorWorldContext().World(), HeadLoc, HeadLoc + 100.0f * TrunkDirProject2Side, 5, FColor(0,255,0), false, 30.0f);
#endif

	if (Angle_Adjust > -3.0f && Angle_Adjust < 3.0f)
		TrunkPositionScore += 1;
	else if (Angle_Adjust > -20.0f && Angle_Adjust < 20.0f)
		TrunkPositionScore += 2;
	else if (Angle_Adjust >= 20.0f && Angle_Adjust <= 60.0f)
		TrunkPositionScore += 3;
	else if (Angle_Adjust <= -20.0f)
		TrunkPositionScore += 3;
	else if (Angle_Adjust > 60.0f)
		TrunkPositionScore += 4;

	/*************************************
		
		Step 2a: Adjust
		
	*************************************/

	//SideBending
	FVector TrunkDirProject2Front = FVector::VectorPlaneProject(TrunkDir, BodyActor->GetActorForwardVector()).GetSafeNormal();
	float RollAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TrunkDirProject2Front, BodyUpDir)));
	if (FMath::Abs(RollAngle) > 5)
		TrunkPositionScore += 1;

	//Twisting
	FTransform HeadTrans = Skeleton->GetSocketTransform(FName(TEXT("head")), ERelativeTransformSpace::RTS_ParentBoneSpace);
	FRotator HeadRot = HeadTrans.Rotator();
	if (FMath::Abs(HeadRot.Roll) > 10)
		TrunkPositionScore += 1;

	TrunkPositionScore = FMath::Clamp<int16>(TrunkPositionScore, 1, 5);

	/*************************************

		Step 3 Legs

	*************************************/

	int16 LegPositionScore = 0;
	FVector RootLoc = Skeleton->GetSocketLocation(FName(TEXT("root")));
	FVector LeftAnkleLoc = Skeleton->GetSocketLocation(FName(TEXT("ball_r")));
	FVector RightAnkleLoc = Skeleton->GetSocketLocation(FName(TEXT("ball_l")));

	bool LeftFootGrounded = FMath::Abs((RootLoc - LeftAnkleLoc).Z) < 10.0f;
	bool RightFootGrounded = FMath::Abs((RootLoc - RightAnkleLoc).Z) < 10.0f;

	if (LeftFootGrounded && RightFootGrounded)
		LegPositionScore += 1;
	else
		LegPositionScore += 2;

	FVector LeftFootLoc = Skeleton->GetSocketLocation(FName(TEXT("foot_l")));
	FVector RightFootLoc = Skeleton->GetSocketLocation(FName(TEXT("foot_r")));
	FVector LeftCalfLoc = Skeleton->GetSocketLocation(FName(TEXT("calf_l")));
	FVector RightCalfLoc = Skeleton->GetSocketLocation(FName(TEXT("calf_r")));
	FVector LeftThighLoc = Skeleton->GetSocketLocation(FName(TEXT("thigh_l")));
	FVector RightThighLoc = Skeleton->GetSocketLocation(FName(TEXT("thigh_r")));

	FVector LeftFoot2Calf = (LeftCalfLoc - LeftFootLoc).GetSafeNormal();
	FVector LeftCalf2Thigh = (LeftThighLoc - LeftCalfLoc).GetSafeNormal();
	float LeftLegAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LeftFoot2Calf, LeftCalf2Thigh)));

	FVector RightFoot2Calf = (RightCalfLoc - RightFootLoc).GetSafeNormal();
	FVector RightCalf2Thigh = (RightThighLoc - RightCalfLoc).GetSafeNormal();
	float RightLegAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightFoot2Calf, RightCalf2Thigh)));

	float AverageLegAngle = (LeftLegAngle + RightLegAngle)*0.5f;
	if (AverageLegAngle < 60 && AverageLegAngle >= 30)
		LegPositionScore += 1;
	else if (AverageLegAngle >= 60)
		LegPositionScore += 2;


	/*************************************

		Step 4 Look-up Posture Score in Table A

	*************************************/

	UE_LOG(LogTemp, Log, TEXT("NeckPositionScore:%d,TrunkPositionScore:%d,LegPositionScore:%d"), NeckPositionScore, TrunkPositionScore, LegPositionScore);
	NeckPositionScore = FMath::Max<int16>(1, NeckPositionScore);
	TrunkPositionScore = FMath::Max<int16>(1, TrunkPositionScore);
	LegPositionScore = FMath::Max<int16>(1, LegPositionScore);

	int16 TableAScore = TableA[NeckPositionScore - 1][TrunkPositionScore - 1][LegPositionScore-1];

	/*************************************

		Step 5 Add Force/Load Score

	*************************************/

	int16 ForceScore = 0;

	if (Load < 5)
		ForceScore += 0;
	else if (Load < 10)
		ForceScore += 1;
	else
		ForceScore += 2;

	if (bShockForce)
		ForceScore += 1;

	/*************************************

		Step 6 ScoreA, Find Row in Table C

	*************************************/
	int16 ScoreA = TableAScore + ForceScore;


	/*************************************

		Table B
		Step 7 Upper Arm Position

	*************************************/

	int16 UpperArmPositionScore=0;

	FVector LeftShoulderLoc = Skeleton->GetSocketLocation(FName(TEXT("upperarm_l")));
	FVector RightShoulderLoc = Skeleton->GetSocketLocation(FName(TEXT("upperarm_r")));
	FVector LeftElbowLoc = Skeleton->GetSocketLocation(FName(TEXT("lowerarm_l")));
	FVector RightElbowLoc = Skeleton->GetSocketLocation(FName(TEXT("lowerarm_r")));

	FVector LeftShoulder2Elbow = LeftElbowLoc - LeftShoulderLoc;
	FVector RightShoulder2Elbow = RightElbowLoc - RightShoulderLoc;
	FVector LeftShoulder2ElbowProject2Side = FVector::VectorPlaneProject(LeftShoulder2Elbow, BodyActor->GetActorRightVector()).GetSafeNormal();
	FVector RightShoulder2ElbowProject2Side = FVector::VectorPlaneProject(RightShoulder2Elbow, BodyActor->GetActorRightVector()).GetSafeNormal();
		
	float LeftUpperArmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LeftShoulder2ElbowProject2Side, BodyActor->GetActorUpVector())));
	float RightUpperArmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightShoulder2ElbowProject2Side, BodyActor->GetActorUpVector())));

	float AverageForarmAngle = (LeftUpperArmAngle + RightUpperArmAngle)*0.5f;
	if (FMath::Abs(AverageForarmAngle) < 20)
		UpperArmPositionScore += 1;
	else if (FMath::Abs(AverageForarmAngle) < 45)
		UpperArmPositionScore += 2;
	else if (FMath::Abs(AverageForarmAngle) < 90)
		UpperArmPositionScore += 3;
	else 
		UpperArmPositionScore += 4;


	/*************************************

		Step 8 Lower Arm Position

	*************************************/

	int16 LowerArmPositionScore = 0;

	FVector LeftHandLoc = Skeleton->GetSocketLocation(FName(TEXT("hand_l")));
	FVector RightHandLoc = Skeleton->GetSocketLocation(FName(TEXT("hand_r")));

	FVector LeftElbow2Hand = LeftHandLoc - LeftElbowLoc;
	FVector RightElbow2Hand = RightHandLoc - RightElbowLoc;

	float LeftLowerArmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LeftShoulder2Elbow,LeftElbow2Hand)));
	float RightLowerArmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightShoulder2Elbow, RightElbow2Hand)));

	float AverageLowerArmAngle = (LeftLowerArmAngle + RightLowerArmAngle)*0.5f;
	if (FMath::Abs(AverageLowerArmAngle) < 60)
		LowerArmPositionScore += 2;
	else if (FMath::Abs(AverageLowerArmAngle) < 100)
		LowerArmPositionScore += 1;
	else
		LowerArmPositionScore += 2;

	/*************************************

		Step 9 Wrist Position

	*************************************/

	int WraistPositionScore = 0;
	FVector RightPalmLoc = Skeleton->GetSocketLocation(FName(TEXT("middle_01_r")));
	FVector LeftPalmLoc = Skeleton->GetSocketLocation(FName(TEXT("middle_01_l")));

	FVector RightPalmVec = RightPalmLoc - RightHandLoc;
	FVector LeftPalmVec = LeftPalmLoc - LeftHandLoc;

	float RightPalmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightPalmVec, RightElbow2Hand)));
	float LeftPalmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LeftPalmVec, LeftElbow2Hand)));

	float AveragePalmAngle = (RightPalmAngle + LeftPalmAngle)*0.5f;

	if (FMath::Abs(AveragePalmAngle) < 15)
		WraistPositionScore += 1;
	else
		WraistPositionScore += 2;

	/*************************************

		Step 10 Posture Score in Table B

	*************************************/
	int16 TableBScore;
	UE_LOG(LogTemp, Log, TEXT("UpperArmPositionScore:%d,LowerArmPositionScore:%d,WraistPositionScore:%d"), UpperArmPositionScore, LowerArmPositionScore, WraistPositionScore);

	//防止=0
	UpperArmPositionScore = FMath::Max<int16>(UpperArmPositionScore, 1);
	LowerArmPositionScore = FMath::Max<int16>(LowerArmPositionScore, 1);
	WraistPositionScore = FMath::Max<int16>(WraistPositionScore, 1);

	TableBScore = TableB[UpperArmPositionScore - 1][LowerArmPositionScore - 1][WraistPositionScore - 1];
	
	/*************************************

		Step 11 Add Coupling Score

	*************************************/
	switch (Coupling)
	{
	case ECoupling_REBA::Good:
		TableBScore += 0;
		break;
	case ECoupling_REBA::Fair:
		TableBScore += 1;
		break;
	case ECoupling_REBA::Poor:
		TableBScore += 2;
		break;
	case ECoupling_REBA::Unacceptable:
		TableBScore += 3;
		break;
	default:
		break;
	}

	/*************************************

		Step 12 Score B

	*************************************/

	int16 ScoreB = TableBScore;

	int16 ScoreC = TableC[ScoreA - 1][ScoreB - 1];

	/*************************************

		Step 13 Activity Score

	*************************************/

	if (bActivityScoreA)
		ScoreC += 1;
	if (bActivityScoreB)
		ScoreC += 1;
	if (bActivityScoreC)
		ScoreC += 1;

	REBAScore = ScoreC;
}
