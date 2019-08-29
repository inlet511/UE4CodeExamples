// Fill out your copyright notice in the Description page of Project Settings.


#include "SRULAWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "SGridPanel.h"
#include "STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "SBox.h"
#include "SCheckBox.h"
#include "SEditableTextBox.h"
#include "ModuleManager.h"
#include "ErgonomicsEditor.h"
#include "RULA.h"
#include "SComboBox.h"

#define LOCTEXT_NAMESPACE "SRULAWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRULAWidget::Construct(const FArguments& InArgs)
{
	//获取当前正在编辑的算法对象
	auto ErgonomicsEditorModule = FModuleManager::LoadModuleChecked<FErgonomicsEditorModule>("ErgonomicsEditor");
	this->EditingRULA = ErgonomicsEditorModule.EditingRULA;

	InitializeDropDownLists();

	ChildSlot
	[
		SNew(SGridPanel)
		.FillColumn(0, 1.0f)
		.FillColumn(1, 5.0f)

		+ SGridPanel::Slot(0, 0)
		.HAlign(HAlign_Center)
		.Padding(5)
		.ColumnSpan(2)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TitleLabel", "RULA(快速上肢评估)"))
		]

	// Column 1
	+ SGridPanel::Slot(0, 1).HAlign(HAlign_Center).ColumnSpan(2).Padding(5)
		[
			SNew(SBox)
			.WidthOverride(200.0f)
			[
				SNew(SButton).ContentPadding(20).HAlign(HAlign_Center)
				.OnClicked(this,&SRULAWidget::CapturePose)
				.Text(LOCTEXT("CapturePose", "捕获姿态"))
			]
		]
	+ SGridPanel::Slot(0, 2).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("ForeArmAdjustment", "前臂调整"))
		]
	+ SGridPanel::Slot(0, 3).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("WristTwist", "手臂弯曲"))
		]
	+ SGridPanel::Slot(0, 4).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("WristMuscle", "腕部肌肉"))
		]
	+ SGridPanel::Slot(0, 5).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("WristLoad", "手臂和腕部承担"))
		]
	+ SGridPanel::Slot(0, 6).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TrunkMuscle", "颈部/躯干/腿部肌肉"))
		]
	+ SGridPanel::Slot(0, 7).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TrunkLoad", "颈部/躯干/腿部承担"))
		]
	+ SGridPanel::Slot(0, 8).HAlign(HAlign_Center).Padding(5)
		.ColumnSpan(2)
		[
			SNew(SButton)
			.ContentPadding(20)
			.OnClicked(this,&SRULAWidget::Evaluate)
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
	+ SGridPanel::Slot(0, 11).HAlign(HAlign_Right).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("RULAScore", "RULA分数"))
		]





		//Column 2
	+ SGridPanel::Slot(1, 2).Padding(5)
		[
			SAssignNew(LowerArmAdjust,SCheckBox)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ForeArmAdjustmentCheckbox", "有没有任何一个前臂越过身体中线或者伸到身体侧方工作"))
			]
		]
	+ SGridPanel::Slot(1, 3).Padding(5)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SAssignNew(ArmBend1,SCheckBox)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("WristTwist1", "手腕是否在中距离上有扭曲"))
				]
			]
		+ SVerticalBox::Slot()
			[
				SAssignNew(ArmBend2,SCheckBox)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("WristTwist2", "手腕是否伸展到或接近极限距离"))
				]
			]
		]
	+ SGridPanel::Slot(1, 4).Padding(5)
		[
			SAssignNew(WristMuscle,SCheckBox)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("WristMuscleCheckbox", "姿势是否主要是静态的（即保持> 1分钟），或者是否重复动作每分钟发生4次或更多。"))
			]
		]
	+SGridPanel::Slot(1,5).Padding(5)
		[
			SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&WraistLoadList)
				.OnGenerateWidget(this, &SRULAWidget::GenerateDropDownItem)
				.OnSelectionChanged(this,&SRULAWidget::HandleWraistLoadChanged)
				[
					SNew(STextBlock)
					.Text(this,&SRULAWidget::GetCurrentWraistLoadText)
				]
		]
	+ SGridPanel::Slot(1, 6).Padding(5)
		[
			SAssignNew(TrunkMuscle,SCheckBox)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("TrunkMuscleCheckbox", "姿势是否主要是静态的（即保持> 1分钟），或者是否重复动作每分钟发生4次或更多。"))
			]
		]
	+SGridPanel::Slot(1,7).Padding(5)
		[
				SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&TrunkLoadList)
				.OnGenerateWidget(this, &SRULAWidget::GenerateDropDownItem)
				.OnSelectionChanged(this,&SRULAWidget::HandleTrunkLoadChanged)
				[
					SNew(STextBlock)
					.Text(this,&SRULAWidget::GetCurrentTrunkLoadText)
				]
		]
	+ SGridPanel::Slot(1, 10).HAlign(HAlign_Left).Padding(5)
		[
			SAssignNew(RI,STextBlock)
			.Text(LOCTEXT("RI_Value", "2.0"))
		]
	+ SGridPanel::Slot(1, 11).HAlign(HAlign_Left).Padding(5)
		[
			SAssignNew(RULAScore,STextBlock)
			.Text(LOCTEXT("RULAScore_Value", "9.00"))
		]
	];

}

FReply SRULAWidget::CapturePose()
{
	return FReply::Handled();
}



FReply SRULAWidget::Evaluate()
{
	return FReply::Handled();
}



void SRULAWidget::InitializeDropDownLists()
{
	WraistLoadList.Empty();
	WraistLoadList.Add(MakeShareable(new FString(TEXT("<2kg(断断续续的)"))));
	WraistLoadList.Add(MakeShareable(new FString(TEXT("2~10kg(断断续续的)"))));
	WraistLoadList.Add(MakeShareable(new FString(TEXT("2~10kg(持续或重复的)"))));
	WraistLoadList.Add(MakeShareable(new FString(TEXT(">10kg(重复或冲击的)"))));

	TrunkLoadList.Empty();
	TrunkLoadList.Add(MakeShareable(new FString(TEXT("<2kg(断断续续的)"))));
	TrunkLoadList.Add(MakeShareable(new FString(TEXT("2~10kg(断断续续的)"))));
	TrunkLoadList.Add(MakeShareable(new FString(TEXT("2~10kg(持续或重复的)"))));
	TrunkLoadList.Add(MakeShareable(new FString(TEXT(">10kg(重复或冲击的)"))));
}

TSharedRef<class SWidget> SRULAWidget::GenerateDropDownItem(TSharedPtr<FString> InItem)
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



FText SRULAWidget::GetCurrentWraistLoadText() const
{
	switch (EditingRULA->WristLoad)
	{
		case ELoadType_RULA::Minimum:
			return FText::FromString(TEXT("<2kg(断断续续的)"));
		case ELoadType_RULA::Light:
			return FText::FromString(TEXT("2~10kg(断断续续的)"));
		case ELoadType_RULA::Medium:
			return FText::FromString(TEXT("2~10kg(持续或重复的)"));
		case ELoadType_RULA::Heavy:
			return FText::FromString(TEXT(">10kg(重复或冲击的)"));

		default:
			return FText::FromString(TEXT("Null"));
	}	
}

void SRULAWidget::HandleWraistLoadChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
		if (*Item == TEXT("<2kg(断断续续的)"))
	{
		EditingRULA->WristLoad = ELoadType_RULA::Minimum;
	}
	else if (*Item == TEXT("2~10kg(断断续续的)"))
	{
		EditingRULA->WristLoad = ELoadType_RULA::Light;
	}
	else if (*Item == TEXT("2~10kg(持续或重复的)"))
	{
		EditingRULA->WristLoad = ELoadType_RULA::Medium;
	}
	else if (*Item == TEXT(">10kg(重复或冲击的)"))
	{
		EditingRULA->WristLoad = ELoadType_RULA::Heavy;
	}
}


FText SRULAWidget::GetCurrentTrunkLoadText() const
{
		switch (EditingRULA->TrunkLoad)
	{
		case ELoadType_RULA::Minimum:
			return FText::FromString(TEXT("<2kg(断断续续的)"));
		case ELoadType_RULA::Light:
			return FText::FromString(TEXT("2~10kg(断断续续的)"));
		case ELoadType_RULA::Medium:
			return FText::FromString(TEXT("2~10kg(持续或重复的)"));
		case ELoadType_RULA::Heavy:
			return FText::FromString(TEXT(">10kg(重复或冲击的)"));

		default:
			return FText::FromString(TEXT("Null"));
	}	
}

void SRULAWidget::HandleTrunkLoadChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("<2kg(断断续续的)"))
	{
		EditingRULA->TrunkLoad = ELoadType_RULA::Minimum;
	}
	else if (*Item == TEXT("2~10kg(断断续续的)"))
	{
		EditingRULA->TrunkLoad = ELoadType_RULA::Light;
	}
	else if (*Item == TEXT("2~10kg(持续或重复的)"))
	{
		EditingRULA->TrunkLoad = ELoadType_RULA::Medium;
	}
	else if (*Item == TEXT(">10kg(重复或冲击的)"))
	{
		EditingRULA->TrunkLoad = ELoadType_RULA::Heavy;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE