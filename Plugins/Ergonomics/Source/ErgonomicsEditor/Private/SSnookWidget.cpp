// Fill out your copyright notice in the Description page of Project Settings.


#include "SSnookWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "Modules/ModuleManager.h"
#include "ErgonomicsEditor.h"
#include "STextBlock.h"
#include "SBox.h"
#include "Snook.h"
#include "SGridPanel.h"
#include "DeclarativeSyntaxSupport.h"
#include "SComboBox.h"
#include "SEditableTextBox.h"

#define LOCTEXT_NAMESPACE "SSnookWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSnookWidget::Construct(const FArguments& InArgs)
{
	//获取当前正在编辑的算法对象
	auto ErgonomicsEditorModule = FModuleManager::LoadModuleChecked<FErgonomicsEditorModule>("ErgonomicsEditor");
	this->EditingSnook = ErgonomicsEditorModule.EditingSnook;

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
			.Text(LOCTEXT("TitleLabel", "Snook表(抬升/放低)"))
		]

	// Column 1
	+ SGridPanel::Slot(0, 1).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("LiftLowerPoint", "抬升/降低点数"))
		]

	+ SGridPanel::Slot(0, 2).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Frequency_Label", "频率"))
		]

	+ SGridPanel::Slot(0, 3).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("HorizontalDistance_Label", "水平手部位置"))
		]

	+ SGridPanel::Slot(0, 4).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("DistanceOfLift_Label", "抬升距离"))
		]

	+ SGridPanel::Slot(0, 5).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("ActuralWeight_Label", "实际重量"))
		]



	+ SGridPanel::Slot(0, 6).HAlign(HAlign_Center).Padding(5)
		.ColumnSpan(2)
		[
			SNew(SButton)
			.ContentPadding(20)
			.OnClicked(this, &SSnookWidget::Evaluate)
			.Text(LOCTEXT("Evaluation", "评估"))
		]

	+ SGridPanel::Slot(0, 7).HAlign(HAlign_Center).Padding(5)
		.ColumnSpan(2)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Result", "结果"))
		]
	+ SGridPanel::Slot(0, 8).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("RI", "风险指数(RI)"))
		]


	//Column 2
	+SGridPanel::Slot(1, 1).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&LiftOverPointList)
				.OnGenerateWidget(this, &SSnookWidget::GenerateDropDownItem)
				.OnSelectionChanged(this, &SSnookWidget::HandleLiftOverPointChanged)
				[
					SNew(STextBlock)
					.Text(this, &SSnookWidget::GetCurrentLiftOverPointText)
				]
			]
		]


	+ SGridPanel::Slot(1, 2).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&FrequencyList)
				.OnGenerateWidget(this, &SSnookWidget::GenerateDropDownItem)
				.OnSelectionChanged(this, &SSnookWidget::HandleFrequencyChanged)
				[
					SNew(STextBlock)
					.Text(this, &SSnookWidget::GetCurrentFrequencyText)
				]
			]
		]

	// 手部水平位置下拉菜单
	+ SGridPanel::Slot(1, 3).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&HorizontalDistanceList)
				.OnGenerateWidget(this, &SSnookWidget::GenerateDropDownItem)
				.OnSelectionChanged(this, &SSnookWidget::HandleHorizontalDistanceChanged)
				[
					SNew(STextBlock)
					.Text(this, &SSnookWidget::GetCurrentHorizontalDistanceText)
				]
			]
		]



	+ SGridPanel::Slot(1, 4).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&LiftDistanceList)
				.OnGenerateWidget(this, &SSnookWidget::GenerateDropDownItem)
				.OnSelectionChanged(this, &SSnookWidget::HandleLiftDistanceChanged)
				[
					SNew(STextBlock)
					.Text(this, &SSnookWidget::GetCurrentLiftDistanceText)
				]
			]
		]


	+ SGridPanel::Slot(1, 5).Padding(5).HAlign(HAlign_Left)
		[
			SNew(SBox).WidthOverride(400.0f)
			[
				SAssignNew(ActualWeight,SEditableTextBox)
			]
		]

	+ SGridPanel::Slot(1, 8).HAlign(HAlign_Left).Padding(5)
		[
			SAssignNew(RI,STextBlock)
			.Text(LOCTEXT("RI_Value", "2.0"))
		]
	];

}


void SSnookWidget::InitializeDropDownLists()
{
	LiftOverPointList.Empty();
	LiftOverPointList.Add(MakeShareable(new FString(TEXT("肩部以上(>137cm)"))));
	LiftOverPointList.Add(MakeShareable(new FString(TEXT("指关节到肩部(74cm~137cm)"))));
	LiftOverPointList.Add(MakeShareable(new FString(TEXT("地面到指关节(<74cm)"))));

	FrequencyList.Empty();
	FrequencyList.Add(MakeShareable(new FString(TEXT("1次/8小时"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1次/30分钟"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1次/5分钟"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1次/2分钟"))));
	FrequencyList.Add(MakeShareable(new FString(TEXT("1次/1分钟"))));

	HorizontalDistanceList.Empty();
	HorizontalDistanceList.Add(MakeShareable(new FString(TEXT("18cm"))));
	HorizontalDistanceList.Add(MakeShareable(new FString(TEXT("25cm"))));
	HorizontalDistanceList.Add(MakeShareable(new FString(TEXT("38cm"))));

	LiftDistanceList.Empty();
	LiftDistanceList.Add(MakeShareable(new FString(TEXT("25cm"))));
	LiftDistanceList.Add(MakeShareable(new FString(TEXT("51cm"))));
	LiftDistanceList.Add(MakeShareable(new FString(TEXT("76cm"))));

}

TSharedRef<class SWidget> SSnookWidget::GenerateDropDownItem(TSharedPtr<FString> InItem)
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


FText SSnookWidget::GetCurrentLiftOverPointText() const
{
	switch (EditingSnook->LiftLowerPoint)
	{
	case ELiftLowerPoint::AboveShoulder:
		return FText::FromString(TEXT("肩部以上(>137cm)"));
	case ELiftLowerPoint::KnuckleToShoulder:
		return FText::FromString(TEXT("指关节到肩部(74cm~137cm)"));
	case ELiftLowerPoint::FloorToKnuckle:
		return FText::FromString(TEXT("地面到指关节(<74cm)"));
	default:
		return FText::FromString(TEXT("Null"));
	}
}

void SSnookWidget::HandleLiftOverPointChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("肩部以上(>137cm)"))
	{
		EditingSnook->LiftLowerPoint = ELiftLowerPoint::AboveShoulder;
	}
	else if (*Item == TEXT("指关节到肩部(74cm~137cm)"))
	{
		EditingSnook->LiftLowerPoint = ELiftLowerPoint::KnuckleToShoulder;
	}
	else if (*Item == TEXT("地面到指关节(<74cm)"))
	{
		EditingSnook->LiftLowerPoint = ELiftLowerPoint::FloorToKnuckle;
	}
}

FText SSnookWidget::GetCurrentFrequencyText() const
{
	switch (EditingSnook->Frequency)
	{
	case EFrequency_Snook::Minimum:
		return FText::FromString(TEXT("1次/8小时"));
	case EFrequency_Snook::Low:
		return FText::FromString(TEXT("1次/30分钟"));
	case EFrequency_Snook::Medium:
		return FText::FromString(TEXT("1次/5分钟"));
	case EFrequency_Snook::High:
		return FText::FromString(TEXT("1次/2分钟"));
	case EFrequency_Snook::Maximum:
		return FText::FromString(TEXT("1次/1分钟"));
	default:
		return FText::FromString(TEXT("Null"));
	}
}

void SSnookWidget::HandleFrequencyChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("1次/8小时"))
	{
		EditingSnook->Frequency = EFrequency_Snook::Minimum;
	}
	else if (*Item == TEXT("1次/30分钟"))
	{
		EditingSnook->Frequency = EFrequency_Snook::Low;
	}
	else if (*Item == TEXT("1次/5分钟"))
	{
		EditingSnook->Frequency = EFrequency_Snook::Medium;
	}
	else if (*Item == TEXT("1次/2分钟"))
	{
		EditingSnook->Frequency = EFrequency_Snook::High;
	}
	else if (*Item == TEXT("1次/1分钟"))
	{
		EditingSnook->Frequency = EFrequency_Snook::Maximum;
	}
}

FText SSnookWidget::GetCurrentHorizontalDistanceText() const
{
	switch (EditingSnook->Distance)
	{
	case EHDistance::Near:
		return FText::FromString(TEXT("18cm"));
	case EHDistance::Medium:
		return FText::FromString(TEXT("25cm"));
	case EHDistance::Far:
		return FText::FromString(TEXT("38cm"));

	default:
		return FText::FromString(TEXT("Null"));
	}
}

void SSnookWidget::HandleHorizontalDistanceChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("18cm"))
	{
		EditingSnook->Distance = EHDistance::Near;
	}
	else if (*Item == TEXT("25cm"))
	{
		EditingSnook->Distance = EHDistance::Medium;
	}
	else if (*Item == TEXT("38cm"))
	{
		EditingSnook->Distance = EHDistance::Far;
	}

}

FText SSnookWidget::GetCurrentLiftDistanceText() const
{
	switch (EditingSnook->LiftDistance)
	{
	case ELiftDistance::Near:
		return FText::FromString(TEXT("25cm"));
	case ELiftDistance::Medium:
		return FText::FromString(TEXT("51cm"));
	case ELiftDistance::Far:
		return FText::FromString(TEXT("76cm"));
	default:
		return FText::FromString(TEXT("Null"));
	}
}

void SSnookWidget::HandleLiftDistanceChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("25cm"))
	{
		EditingSnook->LiftDistance = ELiftDistance::Near;
	}
	else if (*Item == TEXT("51cm"))
	{
		EditingSnook->LiftDistance = ELiftDistance::Medium;
	}
	else if (*Item == TEXT("76cm"))
	{
		EditingSnook->LiftDistance = ELiftDistance::Far;
	}
}


FReply SSnookWidget::Evaluate()
{
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE