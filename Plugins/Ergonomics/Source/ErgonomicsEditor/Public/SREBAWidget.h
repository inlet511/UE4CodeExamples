// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class ERGONOMICSEDITOR_API SREBAWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SREBAWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedPtr<class REBA> EditingREBA;
	//UI�����˵�ѡ��
	TArray<TSharedPtr<FString>> CouplingList;

	//��ʼ��UI�����˵�
	void InitializeDropDownLists();

	TSharedRef<class SWidget> GenerateDropDownItem(TSharedPtr<FString> InItem);

	FText GetCurrentCouplingText() const;
	void HandleCouplingChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);

	FReply Evaluate();
};
