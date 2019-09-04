// Fill out your copyright notice in the Description page of Project Settings.


#include "NIOSH.h"
#include "Components/SkeletalMeshComponent.h"

NIOSH::NIOSH()
{
	Coupling = ECoupling_NIOSH::Good;
	Duration = EDuration_NIOSH::Low;
}

NIOSH::~NIOSH()
{
}

float NIOSH::CalcHM(float InH)
{
	if (InH <= 25.0f)
		return 1.0f;
	else if (InH > 63)
		return 0.0f;
	else
		return 25.0f / InH;	
}

float NIOSH::CalcVM(float InV)
{
	if (InV <= 75.0)
		return 0.003f*InV + 0.78f;
	else if (InV <= 175.0f)
		return -0.003f*InV + 1.2323f;
	else 
		return 0;

}

float NIOSH::CalcDM(float InD)
{
	if (InD <= 25.0f)
		return 1.0f;
	else if (InD > 175.0f)
		return 0;
	else
	{
		return 0.82f + (4.5f / InD);
	}
}

float NIOSH::CalcAM(float InA)
{
	if (InA > 135.0f)
		return 0;
	else
		return 1.0f - 0.0032f*InA;

}

float NIOSH::CalcFM(float InFrequency)
{
	switch (Duration)
	{
	case EDuration_NIOSH::Low:
		if (StartVLocation < 76.2f)
		{
			if (InFrequency <= 0.2f)
				return 1.0f;
			else if (InFrequency < 12.0f)
				return 1.0f + 0.0003f* FMath::Pow(InFrequency, 3.0f) - 0.0078f* FMath::Pow(InFrequency, 2.0f) - 0.0064f * InFrequency;
			else
				return 0.0f;
		}
		else
		{
			if (InFrequency <= 0.2f)
				return 1.0f;
			else if (InFrequency <= 15.0f)
				return 1.0f + 0.0003f* FMath::Pow(InFrequency, 3.0f) - 0.0078f* FMath::Pow(InFrequency, 2.0f) - 0.0064f * InFrequency;
			else
				return 0.0f;
		}
		break;
	case EDuration_NIOSH::Medium:
		if (InFrequency <= 0.2f)
			return 0.95f;
		else
		{
			if (StartVLocation < 76.2f)
			{
				if (InFrequency <= 10.0f)
					return 0.0007f*FMath::Pow(InFrequency, 3.0f) - 0.0117f * FMath::Pow(InFrequency, 2.0f) - 0.0273f*InFrequency + 0.941f;
				else
					return 0.0f;
			}			
			else
			{
				if (InFrequency <= 12.0f)
					return 0.0007f*FMath::Pow(InFrequency, 3.0f) - 0.0117f * FMath::Pow(InFrequency, 2.0f) - 0.0273f*InFrequency + 0.941f;
				else
					return 0.0f;
			}
		}
		break;
	case EDuration_NIOSH::High:
		if (InFrequency <= 0.2f)
			return 0.85f;
		else
		{
			if (StartVLocation < 76.2f)
			{
				if (InFrequency <= 8.0f)
					return 0.0058f * FMath::Pow(InFrequency, 2.0f) - 0.1343f*InFrequency + 0.8827f;
				else
					return 0.0f;
			}			
			else
			{
				if (InFrequency <= 10.0f)
					return 0.0058f * FMath::Pow(InFrequency, 2.0f) - 0.1343f*InFrequency + 0.8827f;
				else
					return 0.0f;
			}
		}
	default:
		return 0.0f;
	}
}

float NIOSH::CalcCM(ECoupling_NIOSH InCoupling)
{
	switch (InCoupling)
	{
	case ECoupling_NIOSH::Good:
			return 1.0f;
	case ECoupling_NIOSH::Fair:
		if (StartVLocation <= 75)
			return 0.95f;
		else
			return 1.0f;
	case ECoupling_NIOSH::Poor:
		return 0.9f;
	default:
		return 0;
	}
}

void NIOSH::SnapshotStartPose()
{
	

	//左脚位置
	FVector FootLeftLoc = Skeleton->GetSocketLocation(FName(TEXT("foot_l")));

	//右脚位置
	FVector FootRightLoc = Skeleton->GetSocketLocation(FName(TEXT("foot_r")));

	//两脚中点
	FVector FootMiddlePoint = (FootLeftLoc + FootRightLoc)*0.5f;

	FTransform RootTrans = Skeleton->GetSocketTransform(FName(TEXT("root")));

	//地面平面
	FPlane RootPlane = FPlane(RootTrans.GetLocation(), RootTrans.GetRotation().GetUpVector());

	//两脚中点在地面的投影
	FVector FootMiddleProject = FPlane::PointPlaneProject(FootMiddlePoint, RootPlane);

	//右手指位置
	FVector HandRightLoc = Skeleton->GetSocketLocation(FName(TEXT("index_01_r")));

	//左手指位置
	FVector HandLeftLoc = Skeleton->GetSocketLocation(FName(TEXT("index_01_l")));

	//两手中点位置
	StartHandMiddlePoint = (HandLeftLoc + HandRightLoc) * 0.5f;

	//两手中点在地面的投影
	FVector HandMiddleProject = FPlane::PointPlaneProject(StartHandMiddlePoint, RootPlane);

	StartHLocation = FVector::Dist(FootMiddleProject, HandMiddleProject);

	StartVLocation = FPlane::PointPlaneDist(HandMiddleProject, RootPlane,RootTrans.GetRotation().GetUpVector());


	StartAsymmetryAngle = CalcAsymmetryAngle();

}

void NIOSH::SnapshotEndPose()
{
	//左脚位置
	FVector FootLeftLoc = Skeleton->GetSocketLocation(FName(TEXT("foot_l")));

	//右脚位置
	FVector FootRightLoc = Skeleton->GetSocketLocation(FName(TEXT("foot_r")));

	//两脚中点
	FVector FootMiddlePoint = (FootLeftLoc + FootRightLoc)*0.5f;

	FTransform RootTrans = Skeleton->GetSocketTransform(FName(TEXT("root")));

	//地面平面
	FPlane RootPlane = FPlane(RootTrans.GetLocation(), RootTrans.GetRotation().GetUpVector());

	//两脚中点在地面的投影
	FVector FootMiddleProject = FPlane::PointPlaneProject(FootMiddlePoint, RootPlane);

	//右手指位置
	FVector HandRightLoc = Skeleton->GetSocketLocation(FName(TEXT("index_01_r")));

	//左手指位置
	FVector HandLeftLoc = Skeleton->GetSocketLocation(FName(TEXT("index_01_l")));

	//两手中点位置
	EndHandMiddlePoint = (HandLeftLoc + HandRightLoc) * 0.5f;

	//两手中点在地面的投影
	FVector HandMiddleProject = FPlane::PointPlaneProject(EndHandMiddlePoint, RootPlane);

	EndHLocation = FVector::Dist(FootMiddleProject, HandMiddleProject);

	EndVLocation = FPlane::PointPlaneDist(HandMiddleProject, RootPlane,RootTrans.GetRotation().GetUpVector());

	
	EndAsymmetryAngle = CalcAsymmetryAngle();
}

float NIOSH::CalcAsymmetryAngle()
{
	FVector ThighL = Skeleton->GetSocketLocation(TEXT("thigh_l"));
	FVector ThighR = Skeleton->GetSocketLocation(TEXT("thigh_r"));
	FVector UpperArmL = Skeleton->GetSocketLocation(TEXT("upperarm_l"));
	FVector UpperArmR = Skeleton->GetSocketLocation(TEXT("upperarm_r"));
	FVector ThighVec = (ThighR - ThighL).GetSafeNormal();
	FVector UpperArmVec = (UpperArmR - UpperArmL).GetSafeNormal();
	return FMath::Acos(FVector::DotProduct(ThighVec, UpperArmVec))*180.0f / 3.1415926f;
}

void NIOSH::Calculate()
{
	HM = CalcHM(StartHLocation);
	VM = CalcVM(StartHLocation);
	DM = CalcVM(FMath::Abs(StartHandMiddlePoint.Z - EndHandMiddlePoint.Z));
	AM = CalcAM(FMath::Abs(StartAsymmetryAngle - EndAsymmetryAngle));
	FM = CalcFM(Frequency);
	CM = CalcCM(Coupling);
	RWL = 23.0f * HM * VM * DM * AM * FM * CM;
	RI = ActualLoad / RWL;
}
