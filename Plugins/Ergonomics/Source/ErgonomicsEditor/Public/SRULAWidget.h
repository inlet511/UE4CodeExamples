// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class ERGONOMICSEDITOR_API SRULAWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRULAWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedPtr<class RULA> EditingRULA;

	//输入控件
	TSharedPtr<SCheckBox> LowerArmAdjust;
	TSharedPtr<SCheckBox> WristTwistMidRange;
	TSharedPtr<SCheckBox> WristNearEndRange;
	TSharedPtr<SCheckBox> WristMuscle;
	TSharedPtr<SCheckBox> TrunkMuscle;

	//输出控件
	TSharedPtr<STextBlock> RI;
	TSharedPtr<STextBlock> RULAScore;

	FReply CapturePose();
	FReply Evaluate();

	TArray<TSharedPtr<FString>> WraistLoadList;
	TArray<TSharedPtr<FString>> TrunkLoadList;

	void InitializeDropDownLists();
	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);

	FText GetCurrentWraistLoadText() const;
	void HandleWraistLoadChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo);

	FText GetCurrentTrunkLoadText() const;
	void HandleTrunkLoadChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo);
};
