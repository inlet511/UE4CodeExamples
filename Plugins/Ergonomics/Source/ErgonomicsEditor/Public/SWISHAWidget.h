// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "WISHA.h"


/**
 * 
 */
class ERGONOMICSEDITOR_API SWISHAWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWISHAWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);





	//UI下拉菜单选项
	TArray<TSharedPtr<FString>> VerticalHandPosList;
	TArray<TSharedPtr<FString>> HorizontalHandPosList;
	TArray<TSharedPtr<FString>> FrequencyList;
	TArray<TSharedPtr<FString>> DurationList;
	TArray<TSharedPtr<FString>> TwistingList;
	


	//输入控件
	TSharedPtr<SEditableTextBox> ActualWeight;

	//输出控件
	TSharedPtr<STextBlock> RI;

private:
	void InitializeDropDownLists();
	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);

	FText GetCurrentVerticalHandPosText() const;
	void HandleVerticalHandPosChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo);

	FText GetCurrentHorizontalHandPosText() const;
	void HandleHorizontalHandPosChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo);

	FText GetCurrentFrequencyText() const;
	void HandleFrequencyChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentDurationText() const;
	void HandleDurationChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo);

	FText GetCurrentTwistText() const;
	void HandleTwistChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo);



	TSharedPtr<class WISHA> EditingWISHA;

	FReply Evaluate();
};
