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

private:
	FReply CapturePose();
	FReply Evaluate();

	TArray<TSharedPtr<FString>> WraistLoadList;
	TArray<TSharedPtr<FString>> TrunkLoadList;

	void InitializeDropDownLists();
	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);
};
