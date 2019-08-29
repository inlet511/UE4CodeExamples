// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class ERGONOMICSEDITOR_API SNIOSHWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNIOSHWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedPtr<class NIOSH> EditingNIOSH;
	TArray<TSharedPtr<FString>> CouplingList;
	TArray<TSharedPtr<FString>> FrequencyList;
	TArray<TSharedPtr<FString>> DurationList;

	//  ‰»Î
	TSharedPtr<SEditableTextBox> HorizontalPos_Start;
	TSharedPtr<SEditableTextBox> HorizontalPos_End;
	TSharedPtr<SEditableTextBox> VerticalPos_Start;
	TSharedPtr<SEditableTextBox> VerticalPos_End;
	TSharedPtr<SEditableTextBox> Asymmetric_Start;
	TSharedPtr<SEditableTextBox> Asymmetric_End;

	// ‰≥ˆ
	TSharedPtr<STextBlock> RI_Start;
	TSharedPtr<STextBlock> RI_End;
	TSharedPtr<STextBlock> RWL_Start;
	TSharedPtr<STextBlock> RWL_End;
	TSharedPtr<STextBlock> HM_Start;
	TSharedPtr<STextBlock> HM_End;
	TSharedPtr<STextBlock> VM_Start;
	TSharedPtr<STextBlock> VM_End;
	TSharedPtr<STextBlock> DM_Start;
	TSharedPtr<STextBlock> DM_End;
	TSharedPtr<STextBlock> AM_Start;
	TSharedPtr<STextBlock> AM_End;
	TSharedPtr<STextBlock> CM_Start;
	TSharedPtr<STextBlock> CM_End;
	TSharedPtr<STextBlock> FM_Start;
	TSharedPtr<STextBlock> FM_End;


	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);

	FText GetCurrentCouplingText() const;
	void HandleCouplingChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentDurationText() const;
	void HandleDurationChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentFrequencyText() const;
	void HandleFrequencyChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	void InitializeDropDownLists();

	FReply CaptureStart();
	FReply CaptureEnd();
	FReply Evaluate();
};
