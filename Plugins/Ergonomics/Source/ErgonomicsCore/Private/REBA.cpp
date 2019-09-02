// Fill out your copyright notice in the Description page of Project Settings.


#include "REBA.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Editor.h"
#include "TransformVectorized.h"

REBA::REBA()
{

// Table A
	TArray<TArray<uint16>> Neck1,Neck2,Neck3;
	TableA.Add(Neck1);
	TableA.Add(Neck2);
	TableA.Add(Neck3);

	TArray<uint16> Trunk11 = { 1,2,3,4 };
	TArray<uint16> Trunk12 = { 2,3,4,5 };
	TArray<uint16> Trunk13 = { 2,4,5,6 };
	TArray<uint16> Trunk14 = { 3,5,6,7 };
	TArray<uint16> Trunk15 = { 4,6,7,8 };

	TArray<uint16> Trunk21 = { 1,2,3,4 };
	TArray<uint16> Trunk22 = { 3,4,5,6 };
	TArray<uint16> Trunk23 = { 4,5,6,7 };
	TArray<uint16> Trunk24 = { 5,6,7,8 };
	TArray<uint16> Trunk25 = { 6,7,8,9 };

	TArray<uint16> Trunk31 = { 3,3,5,6 };
	TArray<uint16> Trunk32 = { 4,5,6,7 };
	TArray<uint16> Trunk33 = { 5,6,7,8 };
	TArray<uint16> Trunk34 = { 6,7,8,9 };
	TArray<uint16> Trunk35 = { 7,8,9,9 };

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



//Table B
	TArray<TArray<uint16>> UpperArm1, UpperArm2, UpperArm3, UpperArm4, UpperArm5, UpperArm6;
	TableB.Add(UpperArm1);
	TableB.Add(UpperArm2);
	TableB.Add(UpperArm3);
	TableB.Add(UpperArm4);
	TableB.Add(UpperArm5);
	TableB.Add(UpperArm6);

	TArray<uint16> LowerArm11 = {1,2,2};
	TArray<uint16> LowerArm12 = {1,2,3};
	TArray<uint16> LowerArm21 = {1,2,3};
	TArray<uint16> LowerArm22 = {2,3,4};
	TArray<uint16> LowerArm31 = {3,4,5};
	TArray<uint16> LowerArm32 = {4,5,5};
	TArray<uint16> LowerArm41 = {4,5,5};
	TArray<uint16> LowerArm42 = {5,6,7};
	TArray<uint16> LowerArm51 = {6,7,8};
	TArray<uint16> LowerArm52 = {7,8,8};
	TArray<uint16> LowerArm61 = {7,8,8};
	TArray<uint16> LowerArm62 = {8,9,9};
	
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

//Table C
	TArray<uint16> ScoreA1 = {1,1,1,2,3,3,4,5,6,7,7,7};
	TArray<uint16> ScoreA2 = {1,2,2,3,4,4,5,6,6,7,7,8};
	TArray<uint16> ScoreA3 = {2,3,3,3,4,5,6,7,7,8,8,8};
	TArray<uint16> ScoreA4 = {3,4,4,4,5,6,7,8,8,9,9,9};
	TArray<uint16> ScoreA5 = {4,4,4,5,6,7,8,8,9,9,9,9};
	TArray<uint16> ScoreA6 = {6,6,6,7,8,8,9,9,10,10,10,10};
	TArray<uint16> ScoreA7 = {7,7,7,8,9,9,9,10,10,11,11,11};
	TArray<uint16> ScoreA8 = {8,8,8,9,10,10,10,10,10,11,11,11};
	TArray<uint16> ScoreA9 = {9,9,9,10,10,10,11,11,11,12,12,12};
	TArray<uint16> ScoreA10 = {10,10,10,11,11,11,11,12,12,12,12,12};
	TArray<uint16> ScoreA11 = {11,11,11,11,12,12,12,12,12,12,12,12};
	TArray<uint16> ScoreA12 = {12,12,12,12,12,12,12,12,12,12,12,12};
	
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
	// Table A, Step 1---------------------------
	FTransform NeckTrans = Skeleton->GetSocketTransform(FName(TEXT("head")), ERelativeTransformSpace::RTS_ParentBoneSpace);

	//在head骨头中，parent space中，左右摇头用Roll表示，  左右Bend 用 Pitch 表示， 前后点头用Yaw表示...
	float NeckRotPitch = NeckTrans.GetRotation().Rotator().Pitch;
	float NeckRotYaw = NeckTrans.GetRotation().Rotator().Yaw + 15.3f;
	float NeckRotRoll = NeckTrans.GetRotation().Rotator().Roll;


	//UE_LOG(LogTemp, Log, TEXT("NeckRotPitch:%f,Yaw:%f,Roll:%f"),NeckRotPitch,NeckRotYaw,NeckRotRoll);
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

	// Table A, Step 2---------------------------
	FVector SpineUp = (Skeleton->GetSocketLocation(FName(TEXT("neck_01"))) - Skeleton->GetSocketLocation(FName(TEXT("pelvis")))).GetSafeNormal();
	FVector ThighRight = Skeleton->GetSocketLocation(FName(TEXT("thigh_r"))) - Skeleton->GetSocketLocation(FName(TEXT("thigh_l")));
	FVector ClavicleRight = Skeleton->GetSocketLocation(FName(TEXT("clavicle_r"))) - Skeleton->GetSocketLocation(FName(TEXT("clavicle_l")));

	FRotator BodyRot = Skeleton->GetSocketRotation(FName(TEXT("pelvis")));
	FVector PelvisLoc = Skeleton->GetSocketLocation(FName(TEXT("pelvis")));
	FVector BodyUpVec = (UKismetMathLibrary::GetForwardVector(BodyRot)).GetSafeNormal();

	
	float TrunkAngle = ((FMath::Acos(FVector::DotProduct(BodyUpVec,SpineUp))) * (180 / 3.1415926));

	UE_LOG(LogTemp, Log, TEXT("TrunkAngle:%f"), TrunkAngle);
	DrawDebugDirectionalArrow(GEditor->GetEditorWorldContext().World(), PelvisLoc, PelvisLoc + 200.0f * UKismetMathLibrary::GetForwardVector(BodyRot), 5, FColor(255,0,0), true, 10.0f);
	DrawDebugDirectionalArrow(GEditor->GetEditorWorldContext().World(), PelvisLoc, PelvisLoc + 200.0f * SpineUp, 5, FColor(0,255,0), true, 10.0f);

}
