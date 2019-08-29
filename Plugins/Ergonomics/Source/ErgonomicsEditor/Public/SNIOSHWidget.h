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

	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);

	FText GetCurrentCouplingText() const;
	void HandleCouplingChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentDurationText() const;
	void HandleDurationChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FText GetCurrentFrequencyText() const;
	void HandleFrequencyChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	void InitializeDropDownLists();
};
