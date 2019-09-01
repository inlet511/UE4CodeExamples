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
	TArray<TSharedPtr<FString>> DurationList;

	//  ‰»Î
	TSharedPtr<SEditableTextBox> HorizontalPos_Start;
	TSharedPtr<SEditableTextBox> HorizontalPos_End;
	TSharedPtr<SEditableTextBox> VerticalPos_Start;
	TSharedPtr<SEditableTextBox> VerticalPos_End;
	TSharedPtr<SEditableTextBox> Asymmetric_Start;
	TSharedPtr<SEditableTextBox> Asymmetric_End;
	TSharedPtr<SEditableTextBox> Frequency_Input;
	TSharedPtr<SEditableTextBox> Weight_Input;


	// ‰≥ˆ
	TSharedPtr<STextBlock> RI;
	TSharedPtr<STextBlock> RWL;
	TSharedPtr<STextBlock> HM;
	TSharedPtr<STextBlock> VM;
	TSharedPtr<STextBlock> DM;
	TSharedPtr<STextBlock> AM;
	TSharedPtr<STextBlock> CM;
	TSharedPtr<STextBlock> FM;



	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);

	FText GetCurrentCouplingText() const;
	void HandleCouplingChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentDurationText() const;
	void HandleDurationChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	void InitializeDropDownLists();

	FReply CaptureStart();
	FReply CaptureEnd();
	FReply Evaluate();
};
