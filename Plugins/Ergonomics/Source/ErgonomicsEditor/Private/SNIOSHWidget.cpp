// Fill out your copyright notice in the Description page of Project Settings.


#include "SNIOSHWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SGridPanel.h"
#include "STextBlock.h"
#include "SSpacer.h"
#include "SEditableTextBox.h"
#include "Widgets/SBoxPanel.h"
#include "SCheckBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "SComboBox.h"
#include "Modules/ModuleManager.h"
#include "NIOSH.h"
#include "ErgonomicsEditor.h"
#include "SWISHAWidget.h"

#define LOCTEXT_NAMESPACE "SNIOSHWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SNIOSHWidget::Construct(const FArguments& InArgs)
{

	//获取当前正在编辑的算法对象
	auto ErgonomicsEditorModule = FModuleManager::LoadModuleChecked<FErgonomicsEditorModule>("ErgonomicsEditor");
	this->EditingNIOSH = ErgonomicsEditorModule.EditingNIOSH;

	//初始化下拉菜单
	InitializeDropDownLists();

	ChildSlot
		[		

				SNew(SGridPanel)
				.FillColumn(0, 0.2f)
				.FillColumn(1, 0.4f)
				.FillColumn(2, 0.4f)

				+ SGridPanel::Slot(0, 0).HAlign(HAlign_Center).Padding(5)
				.ColumnSpan(3)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("TitleLabel", "NIOSH搬举方程"))
				]


				// Column 1
				+ SGridPanel::Slot(0, 1).HAlign(HAlign_Right).Padding(5)
					[
						SNew(SSpacer)
					]
				+ SGridPanel::Slot(0, 2).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HorizontalPos", "横向位置"))
					]
				+ SGridPanel::Slot(0, 3).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("VerticalPos", "纵向位置"))
					]
				+ SGridPanel::Slot(0, 4).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AnglePos", "不对称角度"))
					]
				+ SGridPanel::Slot(0, 5).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Coupling", "耦合度"))
					]
				+ SGridPanel::Slot(0, 6).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Frequency", "频率"))
					]
				+ SGridPanel::Slot(0, 7).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Duration", "持续时间"))
					]
				+ SGridPanel::Slot(0, 8).HAlign(HAlign_Center).ColumnSpan(3).Padding(5,20,5,5)
					[
						SNew(SButton).ContentPadding(20)
						.OnClicked(this,&SNIOSHWidget::Evaluate)
						.Text(LOCTEXT("Evaluation", "评估"))
					]
				+SGridPanel::Slot(0,9)
					[
						SNew(SSpacer)
					]
				+ SGridPanel::Slot(0, 10).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RI", "风险指数(RI)"))
					]
				+ SGridPanel::Slot(0, 11).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RWL", "建议重量限制(RWL,单位kg)"))
					]
				+ SGridPanel::Slot(0, 12).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HM", "HM"))
					]
				+ SGridPanel::Slot(0, 13).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("VM", "VM"))
					]
				+ SGridPanel::Slot(0, 14).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("DM", "DM"))
					]
				+ SGridPanel::Slot(0, 15).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AM", "AM"))
					]
				+ SGridPanel::Slot(0, 16).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("CM", "CM"))
					]
				+ SGridPanel::Slot(0, 17).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("FM", "FM"))
					]



				// Column 2
				+SGridPanel::Slot(1, 1).HAlign(HAlign_Center).Padding(5)
					[
						SNew(SButton)
						.ContentPadding(20).HAlign(HAlign_Center)
						.OnClicked(this,&SNIOSHWidget::CaptureStart)
						.Text(LOCTEXT("CaptureStart", "捕获起点姿态"))
					]

				+ SGridPanel::Slot(1, 2).Padding(5)
					[
						SAssignNew(HorizontalPos_Start,SEditableTextBox)
					]
				+ SGridPanel::Slot(1, 3).Padding(5)
					[
						SAssignNew(VerticalPos_Start,SEditableTextBox)
					]
				+ SGridPanel::Slot(1, 4).Padding(5)
					[
						SAssignNew(Asymmetric_Start,SEditableTextBox)
					]

				+ SGridPanel::Slot(1, 5).Padding(5).ColumnSpan(2)
					[
						SNew(SComboBox<TSharedPtr<FString>>)
						.OptionsSource(&CouplingList)
						.OnGenerateWidget(this, &SNIOSHWidget::GenerateDropDownItem)
						.OnSelectionChanged(this, &SNIOSHWidget::HandleCouplingChanged)
						[
							SNew(STextBlock)
							.Text(this, &SNIOSHWidget::GetCurrentCouplingText)
						]
					]
				+ SGridPanel::Slot(1, 6).Padding(5)
					[
						SNew(SComboBox<TSharedPtr<FString>>)
						.OptionsSource(&FrequencyList)
						.OnGenerateWidget(this, &SNIOSHWidget::GenerateDropDownItem)
						.OnSelectionChanged(this, &SNIOSHWidget::HandleFrequencyChanged)
						[
							SNew(STextBlock)
							.Text(this, &SNIOSHWidget::GetCurrentFrequencyText)
						]
					]
				+ SGridPanel::Slot(1, 7).Padding(5).ColumnSpan(2)
					[
						SNew(SComboBox<TSharedPtr<FString>>)
						.OptionsSource(&DurationList)
						.OnGenerateWidget(this, &SNIOSHWidget::GenerateDropDownItem)
						.OnSelectionChanged(this, &SNIOSHWidget::HandleDurationChanged)
						[
							SNew(STextBlock)
							.Text(this, &SNIOSHWidget::GetCurrentDurationText)
						]
					]
				+ SGridPanel::Slot(1, 9).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("StartSpot", "起点"))
					]
				+ SGridPanel::Slot(1, 10).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(RI_Start,STextBlock)
						.Text(LOCTEXT("RI_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 11).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(RWL_Start,STextBlock)
						.Text(LOCTEXT("RWL_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 12).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(HM_Start,STextBlock)
						.Text(LOCTEXT("HM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 13).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(VM_Start,STextBlock)
						.Text(LOCTEXT("VM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 14).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(DM_Start,STextBlock)
						.Text(LOCTEXT("DM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 15).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(AM_Start,STextBlock)
						.Text(LOCTEXT("AM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 16).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(CM_Start,STextBlock)
						.Text(LOCTEXT("CM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 17).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(FM_Start,STextBlock)
						.Text(LOCTEXT("FM_Start", "0.0"))
					]

				// Column 3
				+ SGridPanel::Slot(2, 1).HAlign(HAlign_Center).Padding(5)
					[
						SNew(SButton)
						.ContentPadding(20).HAlign(HAlign_Center)
						.OnClicked(this,&SNIOSHWidget::CaptureEnd)
						.Text(LOCTEXT("CaptureEnd", "捕获终点姿态"))
					]
				+ SGridPanel::Slot(2, 2).HAlign(HAlign_Fill).Padding(5)
					[
						SAssignNew(HorizontalPos_End,SEditableTextBox)
					]
				+ SGridPanel::Slot(2, 3).HAlign(HAlign_Fill).Padding(5)
					[
						SAssignNew(VerticalPos_End,SEditableTextBox)
					]
				+ SGridPanel::Slot(2, 4).HAlign(HAlign_Fill).Padding(5)
					[
						SAssignNew(Asymmetric_End,SEditableTextBox)
					]
				+ SGridPanel::Slot(2, 6).HAlign(HAlign_Left).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("FrequencyUnit", "次/分钟"))
					]
				+ SGridPanel::Slot(2, 9).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("End", "终点"))
					]
				+ SGridPanel::Slot(2, 10).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(RI_End,STextBlock)
						.Text(LOCTEXT("RI_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 11).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(RWL_End,STextBlock)
						.Text(LOCTEXT("RWL_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 12).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(HM_End,STextBlock)
						.Text(LOCTEXT("HM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 13).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(VM_End,STextBlock)
						.Text(LOCTEXT("VM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 14).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(DM_End,STextBlock)
						.Text(LOCTEXT("DM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 15).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(AM_End,STextBlock)
						.Text(LOCTEXT("AM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 16).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(CM_End,STextBlock)
						.Text(LOCTEXT("CM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 17).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(FM_End,STextBlock)
						.Text(LOCTEXT("FM_End", "0.0"))
					]
			
		];

}


TSharedRef<class SWidget> SNIOSHWidget::GenerateDropDownItem(TSharedPtr<FString> InItem)
{
	FText ItemAsText = FText::FromString(*InItem);
	return
		SNew(SBox)
		.Padding(10)
		.WidthOverride(400)
		[
			SNew(STextBlock)
			.Text(ItemAsText)
			.ToolTipText(ItemAsText)
		];
}

void SNIOSHWidget::InitializeDropDownLists()
{
	CouplingList.Empty();
	CouplingList.Add(MakeShareable(new FString(TEXT("良好"))));
	CouplingList.Add(MakeShareable(new FString(TEXT("一般"))));
	CouplingList.Add(MakeShareable(new FString(TEXT("较差"))));


	FrequencyList.Empty();
	FrequencyList.Add(MakeShareable(new FString(TEXT("等于或低于0.2"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("等于0.5"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("等于1"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("等于2"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("等于3"))));

	DurationList.Empty();
	DurationList.Add(MakeShareable(new FString(TEXT("1小时"))));
	DurationList.Add(MakeShareable(new FString(TEXT("1~2小时"))));
	DurationList.Add(MakeShareable(new FString(TEXT("2~8小时"))));

}



FText SNIOSHWidget::GetCurrentCouplingText() const
{
	switch (EditingNIOSH->Coupling)
	{
	case ECoupling_NIOSH::Good:
		return FText::FromString(TEXT("良好"));
	case ECoupling_NIOSH::Fair:
		return FText::FromString(TEXT("一般"));
	case ECoupling_NIOSH::Poor:
		return FText::FromString(TEXT("较差"));
	default:
		return FText::FromString(TEXT("Null"));
	}
}

void SNIOSHWidget::HandleCouplingChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("良好"))
	{
		EditingNIOSH->Coupling = ECoupling_NIOSH::Good;
	}
	else if (*Item == TEXT("一般"))
	{
		EditingNIOSH->Coupling = ECoupling_NIOSH::Fair;
	}
	else if (*Item == TEXT("较差"))
	{
		EditingNIOSH->Coupling = ECoupling_NIOSH::Poor;
	}

}


FText SNIOSHWidget::GetCurrentDurationText() const
{
	switch (EditingNIOSH->Duration)
	{
		case EDuration_NIOSH::Low:
			return FText::FromString(TEXT("1小时"));
		case EDuration_NIOSH::Medium:
			return FText::FromString(TEXT("1~2小时"));
		case EDuration_NIOSH::High:
			return FText::FromString(TEXT("2~8小时"));
		default:
			return FText::FromString(TEXT("Null"));
	}
}

void SNIOSHWidget::HandleDurationChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("1小时"))
	{
		EditingNIOSH->Duration = EDuration_NIOSH::Low;
	}
	else if (*Item == TEXT("1~2小时"))
	{
		EditingNIOSH->Duration = EDuration_NIOSH::Medium;
	}
	else if (*Item == TEXT("2~8小时"))
	{
		EditingNIOSH->Duration = EDuration_NIOSH::High;
	}
}

FText SNIOSHWidget::GetCurrentFrequencyText() const
{
	switch (EditingNIOSH->Frequency)
	{
	case EFrequency_NIOSH::Minimum:
		return FText::FromString(TEXT("等于或低于0.2"));
	case EFrequency_NIOSH::Low:
		return FText::FromString(TEXT("等于0.5"));
	case EFrequency_NIOSH::Medium:
		return FText::FromString(TEXT("等于1"));
	case EFrequency_NIOSH::High:
		return FText::FromString(TEXT("等于2"));
	case EFrequency_NIOSH::Maximum:
		return FText::FromString(TEXT("等于3"));
	default:
		return FText::FromString(TEXT("Null"));
	}
}

void SNIOSHWidget::HandleFrequencyChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("等于或低于0.2"))
	{
		EditingNIOSH->Frequency = EFrequency_NIOSH::Minimum;
	}
	else if (*Item == TEXT("等于0.5"))
	{
		EditingNIOSH->Frequency = EFrequency_NIOSH::Low;
	}
	else if (*Item == TEXT("等于1"))
	{
		EditingNIOSH->Frequency = EFrequency_NIOSH::Medium;
	}
	else if (*Item == TEXT("等于2"))
	{
		EditingNIOSH->Frequency = EFrequency_NIOSH::High;
	}
	else if (*Item == TEXT("等于3"))
	{
		EditingNIOSH->Frequency = EFrequency_NIOSH::Maximum;
	}
}


FReply SNIOSHWidget::CaptureStart()
{
	return FReply::Handled();
}

FReply SNIOSHWidget::CaptureEnd()
{
	return FReply::Handled();
}

FReply SNIOSHWidget::Evaluate()
{
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE