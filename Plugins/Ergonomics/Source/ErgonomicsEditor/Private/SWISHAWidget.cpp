// Fill out your copyright notice in the Description page of Project Settings.


#include "SWISHAWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "SGridPanel.h"
#include "STextBlock.h"
#include "SSpacer.h"
#include "Widgets/SBoxPanel.h"
#include "SEditableTextBox.h"
#include "SCheckBox.h"
#include "SBox.h"
#include "SComboBox.h"
#include "ErgonomicsEditor.h"
#include "ModuleManager.h"
#include "WISHA.h"

#define LOCTEXT_NAMESPACE "SWISHAWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SWISHAWidget::Construct(const FArguments& InArgs)
{
	//获取当前正在编辑的算法对象
	auto ErgonomicsEditorModule = FModuleManager::LoadModuleChecked<FErgonomicsEditorModule>("ErgonomicsEditor");
	this->EditingWISHA = ErgonomicsEditorModule.EidtingWISHA;

	//初始化下拉菜单	
	InitializeDropDownLists();

	ChildSlot
	[
		SNew(SGridPanel)
		.FillColumn(0, 2.0f)
		.FillColumn(1, 5.0f)

		+ SGridPanel::Slot(0, 0).HAlign(HAlign_Center).Padding(5)
		.ColumnSpan(2)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TitleLabel", "WISHA搬举计算器"))
		]

		// Column 1
		+ SGridPanel::Slot(0, 1).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
		[
			SNew(SSpacer)
		]

		+ SGridPanel::Slot(0, 2).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("ActuralWeight_Label", "实际重量"))
		]

		+ SGridPanel::Slot(0, 3).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("VerticalHandPosition_Label", "垂直手部位置"))
		]

		+ SGridPanel::Slot(0, 4).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("HorizontalHandPosition_Label", "水平手部位置"))
		]

		+ SGridPanel::Slot(0, 5).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Frequency_Label", "频率"))
		]

		+ SGridPanel::Slot(0, 6).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Duration_Label", "持续时间"))
		]

		+ SGridPanel::Slot(0, 7).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Twist_Label", "扭曲"))
		]

		+ SGridPanel::Slot(0, 8).HAlign(HAlign_Center).Padding(5)
		.ColumnSpan(2)
		[
			SNew(SButton)
			.ContentPadding(20)
			.OnClicked(this,&SWISHAWidget::Evaluate)
			.Text(LOCTEXT("Evaluation", "评估"))
		]

		+ SGridPanel::Slot(0, 9).HAlign(HAlign_Center).Padding(5)
		.ColumnSpan(2)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Result", "结果"))
		]
		+ SGridPanel::Slot(0, 10).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("RI", "风险指数(RI)"))
		]


		//Column 2
		+SGridPanel::Slot(1, 2).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[
				SAssignNew(ActualWeight,SEditableTextBox)
			]
		]

		//手部垂直位置下拉菜单
		+SGridPanel::Slot(1, 3).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[					
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&VerticalHandPosList)
				.OnGenerateWidget(this, &SWISHAWidget::GenerateDropDownItem)
				.OnSelectionChanged(this, &SWISHAWidget::HandleVerticalHandPosChanged)
				[
					SNew(STextBlock)
					.Text(this,&SWISHAWidget::GetCurrentVerticalHandPosText)
				]
			]
		]

		// 手部水平位置下拉菜单
		+SGridPanel::Slot(1, 4).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[					
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&HorizontalHandPosList)
				.OnGenerateWidget(this, &SWISHAWidget::GenerateDropDownItem)
				.OnSelectionChanged(this,&SWISHAWidget::HandleHorizontalHandPosChanged)
				[
					SNew(STextBlock)
					.Text(this,&SWISHAWidget::GetCurrentHorizontalHandPosText)
				]
			]
		]

		// 频率下拉菜单
		+SGridPanel::Slot(1, 5).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[					
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&FrequencyList)
				.OnGenerateWidget(this, &SWISHAWidget::GenerateDropDownItem)
				.OnSelectionChanged(this,&SWISHAWidget::HandleFrequencyChanged)
				[
					SNew(STextBlock)
					.Text(this,&SWISHAWidget::GetCurrentFrequencyText)
				]
			]
		]

		// 持续时间下拉菜单
		+SGridPanel::Slot(1, 6).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[					
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&DurationList)
				.OnGenerateWidget(this, &SWISHAWidget::GenerateDropDownItem)
				.OnSelectionChanged(this,&SWISHAWidget::HandleDurationChanged)
				[
					SNew(STextBlock)
					.Text(this,&SWISHAWidget::GetCurrentDurationText)
				]
			]
		]

		// 扭曲下拉菜单
		+SGridPanel::Slot(1, 7).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[					
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&TwistingList)
				.OnGenerateWidget(this, &SWISHAWidget::GenerateDropDownItem)
				.OnSelectionChanged(this,&SWISHAWidget::HandleTwistChanged)
				[
					SNew(STextBlock)					
					.Text(this,&SWISHAWidget::GetCurrentTwistText)
				]
			]
		]

		+ SGridPanel::Slot(1, 10).HAlign(HAlign_Left).Padding(5)
		[
			SAssignNew(RI,STextBlock)
			.Text(LOCTEXT("RI_Value", "2.0"))
		]
	];

}


void SWISHAWidget::InitializeDropDownLists()
{
	VerticalHandPosList.Empty();
	VerticalHandPosList.Add(MakeShareable(new FString(TEXT("肩部以上"))));
	VerticalHandPosList.Add(MakeShareable(new FString(TEXT("腰部到肩部"))));
	VerticalHandPosList.Add(MakeShareable(new FString(TEXT("膝部到腰部"))));
	VerticalHandPosList.Add(MakeShareable(new FString(TEXT("膝部以下"))));
	
	HorizontalHandPosList.Empty();
	HorizontalHandPosList.Add(MakeShareable(new FString(TEXT("<18cm"))));
	HorizontalHandPosList.Add(MakeShareable(new FString(TEXT("18cm~30cm"))));
	HorizontalHandPosList.Add(MakeShareable(new FString(TEXT(">30cm"))));

	FrequencyList.Empty();
	FrequencyList.Add(MakeShareable(new FString(TEXT("2~5分钟1次"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1分钟1次"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1分钟2~3次"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1分钟4~5次"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1分钟6~7次"))));
	

	DurationList.Empty();
	DurationList.Add(MakeShareable(new FString(TEXT("少于等于1小时"))));
	DurationList.Add(MakeShareable(new FString(TEXT("1~2小时"))));
	DurationList.Add(MakeShareable(new FString(TEXT("多于2小时"))));
	
	TwistingList.Empty();
	TwistingList.Add(MakeShareable(new FString(TEXT("小于45度"))));
	TwistingList.Add(MakeShareable(new FString(TEXT("大于等于45度"))));
}

TSharedRef<SWidget> SWISHAWidget::GenerateDropDownItem(TSharedPtr<FString> InItem)
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

FText SWISHAWidget::GetCurrentVerticalHandPosText() const
{
	switch (EditingWISHA->CurrentVerticalHandPos)
	{
		case EVerticalHandPos::AboveShoulder:
			return FText::FromString(TEXT("肩部以上"));
		case EVerticalHandPos::BelowKnee:
			return FText::FromString(TEXT("膝部以下"));
		case EVerticalHandPos::KneeToWaist:
			return FText::FromString(TEXT("膝部到腰部"));
		case EVerticalHandPos::WaistToShoulder:
			return FText::FromString(TEXT("腰部到肩部"));
		default:
			return FText::FromString(TEXT("Null"));
	}	
}

void SWISHAWidget::HandleVerticalHandPosChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("肩部以上"))
	{
		EditingWISHA->CurrentVerticalHandPos = EVerticalHandPos::AboveShoulder;
	}
	else if (*Item == TEXT("膝部以下"))
	{
		EditingWISHA->CurrentVerticalHandPos = EVerticalHandPos::BelowKnee;
	}
	else if (*Item == TEXT("膝部到腰部"))
	{
		EditingWISHA->CurrentVerticalHandPos = EVerticalHandPos::KneeToWaist;
	}
	else if (*Item == TEXT("腰部到肩部"))
	{
		EditingWISHA->CurrentVerticalHandPos = EVerticalHandPos::WaistToShoulder;
	}
}

FText SWISHAWidget::GetCurrentHorizontalHandPosText() const
{
	switch (EditingWISHA->CurrentHorizontalHandPos)
	{
		case EHorizontalHandPos::Near:
			return FText::FromString(TEXT("<18cm"));
		case EHorizontalHandPos::Mid:
			return FText::FromString(TEXT("18cm~30cm"));
		case EHorizontalHandPos::Extended:
			return FText::FromString(TEXT(">30cm"));
		default:
			return FText::FromString(TEXT("Null"));
	}
}

void SWISHAWidget::HandleHorizontalHandPosChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo)
{
		if (*Item == TEXT("<18cm"))
	{
			EditingWISHA->CurrentHorizontalHandPos = EHorizontalHandPos::Near;
	}
	else if (*Item == TEXT("18cm~30cm"))
	{
			EditingWISHA->CurrentHorizontalHandPos = EHorizontalHandPos::Mid;
	}
	else if (*Item == TEXT(">30cm"))
	{
			EditingWISHA->CurrentHorizontalHandPos = EHorizontalHandPos::Extended;
	}

}

FText SWISHAWidget::GetCurrentFrequencyText() const
{
	switch (EditingWISHA->CurrentFrequency)
	{
	case EFrequency::Minimum:
		return FText::FromString(TEXT("2~5分钟1次"));
	case EFrequency::Low:
		return FText::FromString(TEXT("1分钟1次"));
	case EFrequency::Medium:
		return FText::FromString(TEXT("1分钟2~3次"));
	case EFrequency::High:
		return FText::FromString(TEXT("1分钟4~5次"));
	case EFrequency::Maximum:
		return FText::FromString(TEXT("1分钟6~7次"));
	default:
			return FText::FromString(TEXT("Null"));
	}
}

void SWISHAWidget::HandleFrequencyChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("2~5分钟1次"))
	{
		EditingWISHA->CurrentFrequency = EFrequency::Minimum;
	}
	else if (*Item == TEXT("1分钟1次"))
	{
		EditingWISHA->CurrentFrequency = EFrequency::Low;
	}
	else if (*Item == TEXT("1分钟2~3次"))
	{
		EditingWISHA->CurrentFrequency = EFrequency::Medium;
	}
	else if (*Item == TEXT("1分钟4~5次"))
	{
		EditingWISHA->CurrentFrequency = EFrequency::High;
	}
	else if (*Item == TEXT("1分钟6~7次"))
	{
		EditingWISHA->CurrentFrequency = EFrequency::Maximum;
	}
}

FText SWISHAWidget::GetCurrentDurationText() const
{
	switch (EditingWISHA->CurrentDuration)
	{
	case EDuration::Short:
		return FText::FromString(TEXT("少于等于1小时"));
	case EDuration::Medium:
		return FText::FromString(TEXT("1~2小时"));
	case EDuration::Long:
		return FText::FromString(TEXT("多于2小时"));
	
	default:
			return FText::FromString(TEXT("Null"));
	}
}

void SWISHAWidget::HandleDurationChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("少于等于1小时"))
	{
		EditingWISHA->CurrentDuration = EDuration::Short;
	}
	else if (*Item == TEXT("1~2小时"))
	{
		EditingWISHA->CurrentDuration = EDuration::Medium;
	}
	else if (*Item == TEXT("多于2小时"))
	{
		EditingWISHA->CurrentDuration = EDuration::Long;
	}

}

FText SWISHAWidget::GetCurrentTwistText() const
{
	switch (EditingWISHA->CurrentTwist)
	{
		case ETwist::Minor:
			return FText::FromString(TEXT("小于45度"));
		case ETwist::Major:
			return FText::FromString(TEXT("大于等于45度"));	
		default:
				return FText::FromString(TEXT("Null"));
	}
}

void SWISHAWidget::HandleTwistChanged(TSharedPtr<FString> Item,ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("小于45度"))
	{
		EditingWISHA->CurrentTwist = ETwist::Minor;
	}
	else if (*Item == TEXT("大于等于45度"))
	{
		EditingWISHA->CurrentTwist = ETwist::Major;
	}
}



FReply SWISHAWidget::Evaluate()
{
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE