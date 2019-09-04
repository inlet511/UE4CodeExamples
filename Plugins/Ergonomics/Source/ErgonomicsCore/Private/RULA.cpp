// Fill out your copyright notice in the Description page of Project Settings.


#include "RULA.h"
#include "Components/SkeletalMeshComponent.h"

RULA::RULA()
{
	WristLoad = ELoadType_RULA::Minimum;
	TrunkLoad = ELoadType_RULA::Minimum;

	//Table A
	TArray<TArray<TArray<int16>>> UpperArm1, UpperArm2, UpperArm3, UpperArm4, UpperArm5, UpperArm6;
	TArray<TArray<int16>> LowerArm11, LowerArm12, LowerArm13;
	TArray<TArray<int16>> LowerArm21, LowerArm22, LowerArm23;
	TArray<TArray<int16>> LowerArm31, LowerArm32, LowerArm33;
	TArray<TArray<int16>> LowerArm41, LowerArm42, LowerArm43;
	TArray<TArray<int16>> LowerArm51, LowerArm52, LowerArm53;
	TArray<TArray<int16>> LowerArm61, LowerArm62, LowerArm63;

	TArray<int16> WristScore111 = { 1,2 };
	TArray<int16> WristScore112 = { 2,2 };
	TArray<int16> WristScore113 = { 2,3 };
	TArray<int16> WristScore114 = { 3,3 };
	TArray<int16> WristScore121 = { 2,2 };
	TArray<int16> WristScore122 = { 2,2 };
	TArray<int16> WristScore123 = { 3,3 };
	TArray<int16> WristScore124 = { 3,3 };
	TArray<int16> WristScore131 = { 2,3 };
	TArray<int16> WristScore132 = { 3,3 };
	TArray<int16> WristScore133 = { 3,3 };
	TArray<int16> WristScore134 = { 4,4 };
	TArray<int16> WristScore211 = { 2,3 };
	TArray<int16> WristScore212 = { 3,3 };
	TArray<int16> WristScore213 = { 3,4 };
	TArray<int16> WristScore214 = { 4,4 };
	TArray<int16> WristScore221 = { 3,3 };
	TArray<int16> WristScore222 = { 3,3 };
	TArray<int16> WristScore223 = { 3,4 };
	TArray<int16> WristScore224 = { 4,4 };
	TArray<int16> WristScore231 = { 3,4 };
	TArray<int16> WristScore232 = { 4,4 };
	TArray<int16> WristScore233 = { 4,4 };
	TArray<int16> WristScore234 = { 5,5 };
	TArray<int16> WristScore311 = { 3,3 };
	TArray<int16> WristScore312 = { 4,4 };
	TArray<int16> WristScore313 = { 4,4 };
	TArray<int16> WristScore314 = { 5,5 };
	TArray<int16> WristScore321 = { 3,4 };
	TArray<int16> WristScore322 = { 4,4 };
	TArray<int16> WristScore323 = { 4,4 };
	TArray<int16> WristScore324 = { 5,5 };
	TArray<int16> WristScore331 = { 4,4 };
	TArray<int16> WristScore332 = { 4,4 };
	TArray<int16> WristScore333 = { 4,5 };
	TArray<int16> WristScore334 = { 5,5 };
	TArray<int16> WristScore411 = { 4,4 };
	TArray<int16> WristScore412 = { 4,4 };
	TArray<int16> WristScore413 = { 4,5 };
	TArray<int16> WristScore414 = { 5,5 };
	TArray<int16> WristScore421 = { 4,4 };
	TArray<int16> WristScore422 = { 4,4 };
	TArray<int16> WristScore423 = { 4,5 };
	TArray<int16> WristScore424 = { 5,5 };
	TArray<int16> WristScore431 = { 4,4 };
	TArray<int16> WristScore432 = { 4,5 };
	TArray<int16> WristScore433 = { 5,5 };
	TArray<int16> WristScore434 = { 6,6 };
	TArray<int16> WristScore511 = { 5,5 };
	TArray<int16> WristScore512 = { 5,5 };
	TArray<int16> WristScore513 = { 5,6 };
	TArray<int16> WristScore514 = { 6,7 };
	TArray<int16> WristScore521 = { 5,6 };
	TArray<int16> WristScore522 = { 6,6 };
	TArray<int16> WristScore523 = { 6,7 };
	TArray<int16> WristScore524 = { 7,7 };
	TArray<int16> WristScore531 = { 6,6 };
	TArray<int16> WristScore532 = { 6,7 };
	TArray<int16> WristScore533 = { 7,7 };
	TArray<int16> WristScore534 = { 7,8 };
	TArray<int16> WristScore611 = { 7,7 };
	TArray<int16> WristScore612 = { 7,7 };
	TArray<int16> WristScore613 = { 7,8 };
	TArray<int16> WristScore614 = { 8,9 };
	TArray<int16> WristScore621 = { 8,8 };
	TArray<int16> WristScore622 = { 8,8 };
	TArray<int16> WristScore623 = { 8,9 };
	TArray<int16> WristScore624 = { 9,9 };
	TArray<int16> WristScore631 = { 9,9 };
	TArray<int16> WristScore632 = { 9,9 };
	TArray<int16> WristScore633 = { 9,9 };
	TArray<int16> WristScore634 = { 9,9 };

	LowerArm11.Add(WristScore111);
	LowerArm11.Add(WristScore112);
	LowerArm11.Add(WristScore113);
	LowerArm11.Add(WristScore114);

	LowerArm12.Add(WristScore121);
	LowerArm12.Add(WristScore122);
	LowerArm12.Add(WristScore123);
	LowerArm12.Add(WristScore124);

	LowerArm13.Add(WristScore131);
	LowerArm13.Add(WristScore132);
	LowerArm13.Add(WristScore133);
	LowerArm13.Add(WristScore134);

	LowerArm21.Add(WristScore211);
	LowerArm21.Add(WristScore212);
	LowerArm21.Add(WristScore213);
	LowerArm21.Add(WristScore214);

	LowerArm22.Add(WristScore221);
	LowerArm22.Add(WristScore222);
	LowerArm22.Add(WristScore223);
	LowerArm22.Add(WristScore224);

	LowerArm23.Add(WristScore231);
	LowerArm23.Add(WristScore232);
	LowerArm23.Add(WristScore233);
	LowerArm23.Add(WristScore234);

	LowerArm31.Add(WristScore311);
	LowerArm31.Add(WristScore312);
	LowerArm31.Add(WristScore313);
	LowerArm31.Add(WristScore314);

	LowerArm32.Add(WristScore321);
	LowerArm32.Add(WristScore322);
	LowerArm32.Add(WristScore323);
	LowerArm32.Add(WristScore324);

	LowerArm33.Add(WristScore331);
	LowerArm33.Add(WristScore332);
	LowerArm33.Add(WristScore333);
	LowerArm33.Add(WristScore334);

	LowerArm41.Add(WristScore411);
	LowerArm41.Add(WristScore412);
	LowerArm41.Add(WristScore413);
	LowerArm41.Add(WristScore414);

	LowerArm42.Add(WristScore421);
	LowerArm42.Add(WristScore422);
	LowerArm42.Add(WristScore423);
	LowerArm42.Add(WristScore424);

	LowerArm43.Add(WristScore431);
	LowerArm43.Add(WristScore432);
	LowerArm43.Add(WristScore433);
	LowerArm43.Add(WristScore434);

	LowerArm51.Add(WristScore511);
	LowerArm51.Add(WristScore512);
	LowerArm51.Add(WristScore513);
	LowerArm51.Add(WristScore514);

	LowerArm52.Add(WristScore521);
	LowerArm52.Add(WristScore522);
	LowerArm52.Add(WristScore523);
	LowerArm52.Add(WristScore524);

	LowerArm53.Add(WristScore531);
	LowerArm53.Add(WristScore532);
	LowerArm53.Add(WristScore533);
	LowerArm53.Add(WristScore534);

	LowerArm61.Add(WristScore611);
	LowerArm61.Add(WristScore612);
	LowerArm61.Add(WristScore613);
	LowerArm61.Add(WristScore614);

	LowerArm62.Add(WristScore621);
	LowerArm62.Add(WristScore622);
	LowerArm62.Add(WristScore623);
	LowerArm62.Add(WristScore624);

	LowerArm63.Add(WristScore631);
	LowerArm63.Add(WristScore632);
	LowerArm63.Add(WristScore633);
	LowerArm63.Add(WristScore634);

	UpperArm1.Add(LowerArm11);
	UpperArm1.Add(LowerArm12);
	UpperArm1.Add(LowerArm13);

	UpperArm2.Add(LowerArm21);
	UpperArm2.Add(LowerArm22);
	UpperArm2.Add(LowerArm23);

	UpperArm3.Add(LowerArm13);
	UpperArm3.Add(LowerArm13);
	UpperArm3.Add(LowerArm13);

	UpperArm4.Add(LowerArm41);
	UpperArm4.Add(LowerArm42);
	UpperArm4.Add(LowerArm43);

	UpperArm5.Add(LowerArm51);
	UpperArm5.Add(LowerArm52);
	UpperArm5.Add(LowerArm53);

	UpperArm6.Add(LowerArm61);
	UpperArm6.Add(LowerArm62);
	UpperArm6.Add(LowerArm63);

	TableA.Add(UpperArm1);
	TableA.Add(UpperArm2);
	TableA.Add(UpperArm3);
	TableA.Add(UpperArm4);
	TableA.Add(UpperArm5);
	TableA.Add(UpperArm6);


	//Table B
	TArray<TArray<int16>> NeckPosition1;
	TArray<TArray<int16>> NeckPosition2;
	TArray<TArray<int16>> NeckPosition3;
	TArray<TArray<int16>> NeckPosition4;
	TArray<TArray<int16>> NeckPosition5;
	TArray<TArray<int16>> NeckPosition6;

	TArray<int16> TrunkPosition11 = { 1,3 };
	TArray<int16> TrunkPosition12 = { 2,3 };
	TArray<int16> TrunkPosition13 = { 3,4 };
	TArray<int16> TrunkPosition14 = { 5,5 };
	TArray<int16> TrunkPosition15 = { 6,6 };
	TArray<int16> TrunkPosition16 = { 7,7 };

	TArray<int16> TrunkPosition21 = { 2,3 };
	TArray<int16> TrunkPosition22 = { 2,3 };
	TArray<int16> TrunkPosition23 = { 4,5 };
	TArray<int16> TrunkPosition24 = { 5,5 };
	TArray<int16> TrunkPosition25 = { 6,7 };
	TArray<int16> TrunkPosition26 = { 7,7 };

	TArray<int16> TrunkPosition31 = { 3,3 };
	TArray<int16> TrunkPosition32 = { 3,4 };
	TArray<int16> TrunkPosition33 = { 4,5 };
	TArray<int16> TrunkPosition34 = { 5,6 };
	TArray<int16> TrunkPosition35 = { 6,7 };
	TArray<int16> TrunkPosition36 = { 7,7 };

	TArray<int16> TrunkPosition41 = { 5,5 };
	TArray<int16> TrunkPosition42 = { 5,6 };
	TArray<int16> TrunkPosition43 = { 6,7 };
	TArray<int16> TrunkPosition44 = { 7,7 };
	TArray<int16> TrunkPosition45 = { 7,7 };
	TArray<int16> TrunkPosition46 = { 8,8 };

	TArray<int16> TrunkPosition51 = { 7,7 };
	TArray<int16> TrunkPosition52 = { 7,7 };
	TArray<int16> TrunkPosition53 = { 7,8 };
	TArray<int16> TrunkPosition54 = { 8,8 };
	TArray<int16> TrunkPosition55 = { 8,8 };
	TArray<int16> TrunkPosition56 = { 8,8 };

	TArray<int16> TrunkPosition61 = { 8,8 };
	TArray<int16> TrunkPosition62 = { 8,8 };
	TArray<int16> TrunkPosition63 = { 8,8 };
	TArray<int16> TrunkPosition64 = { 8,9 };
	TArray<int16> TrunkPosition65 = { 9,9 };
	TArray<int16> TrunkPosition66 = { 9,9 };

	NeckPosition1.Add(TrunkPosition11);
	NeckPosition1.Add(TrunkPosition12);
	NeckPosition1.Add(TrunkPosition13);
	NeckPosition1.Add(TrunkPosition14);
	NeckPosition1.Add(TrunkPosition15);
	NeckPosition1.Add(TrunkPosition16);

	NeckPosition2.Add(TrunkPosition21);
	NeckPosition2.Add(TrunkPosition22);
	NeckPosition2.Add(TrunkPosition23);
	NeckPosition2.Add(TrunkPosition24);
	NeckPosition2.Add(TrunkPosition25);
	NeckPosition2.Add(TrunkPosition26);

	NeckPosition3.Add(TrunkPosition21);
	NeckPosition3.Add(TrunkPosition22);
	NeckPosition3.Add(TrunkPosition23);
	NeckPosition3.Add(TrunkPosition24);
	NeckPosition3.Add(TrunkPosition25);
	NeckPosition3.Add(TrunkPosition26);

	NeckPosition4.Add(TrunkPosition41);
	NeckPosition4.Add(TrunkPosition42);
	NeckPosition4.Add(TrunkPosition43);
	NeckPosition4.Add(TrunkPosition44);
	NeckPosition4.Add(TrunkPosition45);
	NeckPosition4.Add(TrunkPosition46);

	NeckPosition5.Add(TrunkPosition51);
	NeckPosition5.Add(TrunkPosition52);
	NeckPosition5.Add(TrunkPosition53);
	NeckPosition5.Add(TrunkPosition54);
	NeckPosition5.Add(TrunkPosition55);
	NeckPosition5.Add(TrunkPosition56);

	NeckPosition6.Add(TrunkPosition61);
	NeckPosition6.Add(TrunkPosition62);
	NeckPosition6.Add(TrunkPosition63);
	NeckPosition6.Add(TrunkPosition64);
	NeckPosition6.Add(TrunkPosition65);
	NeckPosition6.Add(TrunkPosition66);
	
	TableB.Add(NeckPosition1);
	TableB.Add(NeckPosition2);
	TableB.Add(NeckPosition3);
	TableB.Add(NeckPosition4);
	TableB.Add(NeckPosition5);
	TableB.Add(NeckPosition6);

	//Table C
	TArray<int16> WristArmScore1 = { 1,2,3,3,4,5,5 };
	TArray<int16> WristArmScore2 = { 2,2,3,4,4,5,5 };
	TArray<int16> WristArmScore3 = { 3,3,3,4,4,5,6 };
	TArray<int16> WristArmScore4 = { 3,3,3,4,5,6,6 };
	TArray<int16> WristArmScore5 = { 4,4,4,5,6,7,7 };
	TArray<int16> WristArmScore6 = { 4,4,5,6,6,7,7 };
	TArray<int16> WristArmScore7 = { 5,5,6,6,7,7,7 };
	TArray<int16> WristArmScore8 = { 5,5,6,7,7,7,7 };

	TableC.Add(WristArmScore1);
	TableC.Add(WristArmScore2);
	TableC.Add(WristArmScore3);
	TableC.Add(WristArmScore4);
	TableC.Add(WristArmScore5);
	TableC.Add(WristArmScore6);
	TableC.Add(WristArmScore7);
	TableC.Add(WristArmScore8);

}

RULA::~RULA()
{
}

void RULA::SnapshotPose()
{

	AActor* BodyActor = Skeleton->GetOwner();
	/*************************************
		
		Table A
		Step 1 Upper Arm Position 

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

		Step 2 Lower Arm Position

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

	if (bLowerArmAdjustments)
		LowerArmPositionScore += 1;

	/*************************************

		Step 3 Wrist Position

	*************************************/

	int WraistPositionScore = 0;
	FVector RightPalmLoc = Skeleton->GetSocketLocation(FName(TEXT("middle_01_r")));
	FVector LeftPalmLoc = Skeleton->GetSocketLocation(FName(TEXT("middle_01_l")));

	FVector RightPalmVec = RightPalmLoc - RightHandLoc;
	FVector LeftPalmVec = LeftPalmLoc - LeftHandLoc;

	float RightPalmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightPalmVec, RightElbow2Hand)));
	float LeftPalmAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(LeftPalmVec, LeftElbow2Hand)));

	float AveragePalmAngle = (RightPalmAngle + LeftPalmAngle)*0.5f;

	if (FMath::Abs(AveragePalmAngle) < 3)
		WraistPositionScore += 1;
	else if(FMath::Abs(AveragePalmAngle) < 15)
		WraistPositionScore += 2;
	else 
		WraistPositionScore += 3;

	/*************************************

		Step 4 Wrist Twist

	*************************************/

	int16 WristTwistScore = 0;
	if (bWristTwistMidRange)
		WristTwistScore += 1;
	if (bWristNearEndRange)
		WristTwistScore += 2;

	/*************************************

		Step 5 Wrist Position

	*************************************/

	UpperArmPositionScore = FMath::Max<int16>(1, UpperArmPositionScore);
	LowerArmPositionScore = FMath::Max<int16>(1, LowerArmPositionScore);
	WraistPositionScore = FMath::Clamp<int16>(WristTwistScore, 1, 4);
	WristTwistScore = FMath::Clamp<int16>(WristTwistScore, 1, 2);
	int16 TableAScore = TableA[UpperArmPositionScore - 1][LowerArmPositionScore - 1][WraistPositionScore - 1][WristTwistScore - 1];

	/*************************************

		Step 6 Add Muscle Use Score

	*************************************/
	int16 WristMuscleUseScore = 0;
	if (bWristMuscleUse)
		WristMuscleUseScore += 1;


	/*************************************

		Step 7 Add ForceLoad Score

	*************************************/

	int16 WristForceScore = 0;

	switch (WristLoad)
	{
	case ELoadType_RULA::Minimum:
		WristForceScore += 0;
		break;
	case ELoadType_RULA::Light:
		WristForceScore += 1;
		break;
	case ELoadType_RULA::Medium:
		WristForceScore += 2;
		break;
	case ELoadType_RULA::Heavy:
		WristForceScore += 3;
		break;
	default:
		break;
	}

	/*************************************

		Step 8 Add ForceLoad Score

	*************************************/

	int16 TableCRow = TableAScore + WristMuscleUseScore + WristForceScore;


	
	/*************************************

		Step 9 Neck Position

	*************************************/


	FTransform NeckTrans = Skeleton->GetSocketTransform(FName(TEXT("head")), ERelativeTransformSpace::RTS_ParentBoneSpace);

	//在head bone 中，parent space中，左右摇头用Roll表示，  左右Bend 用 Pitch 表示， 前后点头用Yaw表示...
	float NeckRotPitch = NeckTrans.GetRotation().Rotator().Pitch;
	float NeckRotYaw = NeckTrans.GetRotation().Rotator().Yaw + 15.3f;
	float NeckRotRoll = NeckTrans.GetRotation().Rotator().Roll;

	int16 NeckPositionScore = 0;
	if (NeckRotYaw > 0) {
		if (NeckRotYaw <= 10)
			NeckPositionScore += 1;
		else if (NeckRotYaw <= 20)
			NeckPositionScore += 2;
		else 
			NeckPositionScore += 3;
	}
	else
	{
		NeckPositionScore += 4;
	}


	if (FMath::Abs(NeckRotRoll) > 5)
		NeckPositionScore += 1;
	if (FMath::Abs(NeckRotPitch) > 5)
		NeckPositionScore += 1;

	/*************************************

		Step 10 Trunk Position

	*************************************/

	int16 TrunkPositionScore = 0;
	FVector TrunkDir = (Skeleton->GetSocketLocation(FName(TEXT("neck_01"))) - Skeleton->GetSocketLocation(FName(TEXT("pelvis")))).GetSafeNormal();

	//躯干向量投影到平面上的向量
	FVector TrunkDirProject2Side = FVector::VectorPlaneProject(TrunkDir, BodyActor->GetActorRightVector()).GetSafeNormal();

	FVector BodyUpDir = (BodyActor->GetActorUpVector()).GetSafeNormal();
	FVector CrossProductResult = FVector::CrossProduct(TrunkDirProject2Side, BodyUpDir);

	float PitchAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TrunkDirProject2Side, BodyUpDir)));
	float PitchSign = FVector::DotProduct(CrossProductResult, BodyActor->GetActorRightVector()) >= 0 ? 1 : -1;

	//根据正常站姿调整,并调整符号
	float Angle_Adjust = -1.0f * (PitchAngle * PitchSign - 4.62f);

	if (Angle_Adjust > -3.0f && Angle_Adjust < 3.0f)
		TrunkPositionScore += 1;
	else if (Angle_Adjust > 0 && Angle_Adjust < 20.0f)
		TrunkPositionScore += 2;
	else if (Angle_Adjust >= 20.0f && Angle_Adjust <= 60.0f)
		TrunkPositionScore += 3;
	else if (Angle_Adjust > 60.0f)
		TrunkPositionScore += 4;

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

	/*************************************

		Step 11 Legs

	*************************************/

	// TODO

	/*************************************

		Step 12 Posture Score in Table B

	*************************************/

	NeckPositionScore = FMath::Max<int16>(NeckPositionScore, 1);
	TrunkPositionScore = FMath::Max<int16>(TrunkPositionScore, 1);

	int16 TableBScore = TableB[NeckPositionScore - 1][TrunkPositionScore - 1][1];

	/*************************************

		Step 13 Add Trunk Muscle Use Score

	*************************************/

	int16 TrunkMuscleUseScore = 0;
	if (bTrunkMuscleUse)
		TrunkMuscleUseScore += 1;


	/*************************************

		Step 14 Add Trunk Force/Load Score

	*************************************/

	int16 TrunkForceScore = 0;

	switch (TrunkLoad)
	{
	case ELoadType_RULA::Minimum:
		TrunkForceScore += 0;
		break;
	case ELoadType_RULA::Light:
		TrunkForceScore += 1;
		break;
	case ELoadType_RULA::Medium:
		TrunkForceScore += 2;
		break;
	case ELoadType_RULA::Heavy:
		TrunkForceScore += 3;
		break;
	default:
		break;
	}

	/*************************************

		Step 15 Find Column in Table C

	*************************************/
	int16 TableCColumn = TableBScore + TrunkMuscleUseScore + TrunkForceScore;
	TableCColumn = FMath::Clamp<int16>(TableCColumn, 1, 7);

	TableCRow = FMath::Clamp<int16>(TableCRow, 1, 8);

	RULAScore = TableC[TableCRow - 1][TableCColumn - 1];
}
