// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class ERGONOMICSEDITOR_API SSnookWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSnookWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedPtr<class Snook> EditingSnook;

	//UI下拉菜单选项
	TArray<TSharedPtr<FString>> LiftOverPointList;
	TArray<TSharedPtr<FString>> FrequencyList;
	TArray<TSharedPtr<FString>> HorizontalDistanceList;
	TArray<TSharedPtr<FString>> LiftDistanceList;

	TSharedPtr<class SEditableTextBox> ActualWeight;
	void HandleActualWeightCommit(const FText& InText, ETextCommit::Type InCommitType);

	void InitializeDropDownLists();
	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);

	FText GetCurrentLiftOverPointText() const;
	void HandleLiftOverPointChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentFrequencyText() const;
	void HandleFrequencyChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentHorizontalDistanceText() const;
	void HandleHorizontalDistanceChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentLiftDistanceText() const;
	void HandleLiftDistanceChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FReply Evaluate();

	

};
