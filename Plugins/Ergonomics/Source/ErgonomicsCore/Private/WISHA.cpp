// Fill out your copyright notice in the Description page of Project Settings.


#include "WISHA.h"

WISHA::WISHA()
{
	CurrentVerticalHandPos = EVerticalHandPos::AboveShoulder;
	CurrentHorizontalHandPos = EHorizontalHandPos::Near;
	CurrentFrequency = EFrequency::Minimum;
	CurrentDuration = EDuration::Short;
	CurrentTwist = ETwist::Minor;
}

WISHA::~WISHA()
{
}

void WISHA::Evaluate()
{
	/*************************************

	Step 2 UnAdjustedWeightLimit

	*************************************/
	UnadjustedWeightLimit = 0;
	switch (CurrentVerticalHandPos)
	{
	case EVerticalHandPos::AboveShoulder:
		switch (CurrentHorizontalHandPos)
		{
		case EHorizontalHandPos::Near:
			UnadjustedWeightLimit = 29.5f;
			break;
		case EHorizontalHandPos::Mid:
			UnadjustedWeightLimit = 18.0f;
			break;
		case EHorizontalHandPos::Extended:
			UnadjustedWeightLimit = 13.6f;
			break;
		default:
			break;
		}
		break;
	case EVerticalHandPos::WaistToShoulder:
		switch (CurrentHorizontalHandPos)
		{
		case EHorizontalHandPos::Near:
			UnadjustedWeightLimit = 31.75f;
			break;
		case EHorizontalHandPos::Mid:
			UnadjustedWeightLimit = 22.68f;
			break;
		case EHorizontalHandPos::Extended:
			UnadjustedWeightLimit = 18;
			break;
		default:
			break;
		}
		break;
	case EVerticalHandPos::KneeToWaist:
		switch (CurrentHorizontalHandPos)
		{
		case EHorizontalHandPos::Near:
			UnadjustedWeightLimit = 40.82f;
			break;
		case EHorizontalHandPos::Mid:
			UnadjustedWeightLimit = 24.95f;
			break;
		case EHorizontalHandPos::Extended:
			UnadjustedWeightLimit = 18.14f;
			break;
		default:
			break;
		}
		break;
	case EVerticalHandPos::BelowKnee:
		switch (CurrentHorizontalHandPos)
		{
		case EHorizontalHandPos::Near:
			UnadjustedWeightLimit = 31.75f;
			break;
		case EHorizontalHandPos::Mid:
			UnadjustedWeightLimit = 22.68f;
			break;
		case EHorizontalHandPos::Extended:
			UnadjustedWeightLimit = 15.88f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	/*************************************

		Step 3 LimitReductionModifier

	*************************************/
	LimitReductionModifier = 1.0f;

	switch (CurrentFrequency)
	{
	case EFrequency::Minimum:
		switch (CurrentDuration)
		{
		case EDuration::Short:
			LimitReductionModifier = 1.0f;
			break;
		case EDuration::Medium:
			LimitReductionModifier = 0.95f;
			break;
		case EDuration::Long:
			LimitReductionModifier = 0.85f;
			break;
		default:
			break;
		}
		break;
	case EFrequency::Low:
		switch (CurrentDuration)
		{
		case EDuration::Short:
			LimitReductionModifier = 0.95f;
			break;
		case EDuration::Medium:
			LimitReductionModifier = 0.9f;
			break;
		case EDuration::Long:
			LimitReductionModifier = 0.75f;
			break;
		default:
			break;
		}
		break;
	case EFrequency::Medium:
		switch (CurrentDuration)
		{
		case EDuration::Short:
			LimitReductionModifier = 0.9f;
			break;
		case EDuration::Medium:
			LimitReductionModifier = 0.85f;
			break;
		case EDuration::Long:
			LimitReductionModifier = 0.65f;
			break;
		default:
			break;
		}
		break;
	case EFrequency::High:
		switch (CurrentDuration)
		{
		case EDuration::Short:
			LimitReductionModifier = 0.85f;
			break;
		case EDuration::Medium:
			LimitReductionModifier = 0.7f;
			break;
		case EDuration::Long:
			LimitReductionModifier = 0.45f;
			break;
		default:
			break;
		}
		break;
	case EFrequency::VeryHigh:
		switch (CurrentDuration)
		{
		case EDuration::Short:
			LimitReductionModifier = 0.75f;
			break;
		case EDuration::Medium:
			LimitReductionModifier = 0.5f;
			break;
		case EDuration::Long:
			LimitReductionModifier = 0.25f;
			break;
		default:
			break;
		}
		break;
	case EFrequency::Extra:
		switch (CurrentDuration)
		{
		case EDuration::Short:
			LimitReductionModifier = 0.6f;
			break;
		case EDuration::Medium:
			LimitReductionModifier = 0.35f;
			break;
		case EDuration::Long:
			LimitReductionModifier = 0.15f;
			break;
		default:
			break;
		}
		break;
	case EFrequency::Maximum:
		switch (CurrentDuration)
		{
		case EDuration::Short:
			LimitReductionModifier = 0.3f;
			break;
		case EDuration::Medium:
			LimitReductionModifier = 0.2f;
			break;
		case EDuration::Long:
			LimitReductionModifier = 0.0f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}


	/*************************************

	Step 4 Adjusted Weight Limit

	*************************************/
	switch (CurrentTwist)
	{
	case ETwist::Minor:
		AdjustedWeightLimit = UnadjustedWeightLimit * 0.85f;
		break;
	case ETwist::Major:
		AdjustedWeightLimit = UnadjustedWeightLimit;
		break;
	default:
		break;
	}
	/*************************************

	Step 5 Weight Limit

	*************************************/
	WeightLimit = AdjustedWeightLimit * LimitReductionModifier;

	/*************************************

	Step 6 RI

	*************************************/

	RI = ActuralWeight / WeightLimit;
}
