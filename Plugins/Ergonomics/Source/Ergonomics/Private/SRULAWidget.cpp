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
#define LOCTEXT_NAMESPACE "SRULAWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRULAWidget::Construct(const FArguments& InArgs)
{

	ChildSlot
	[
		SNew(SGridPanel)
		.FillColumn(0, 1.0f)
		.FillColumn(1, 5.0f)

		+ SGridPanel::Slot(0, 0).HAlign(HAlign_Center).Padding(5)
		.ColumnSpan(2)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TitleLabel", "RULA(快速上肢评估)"))
		]

	// Column 1
	+ SGridPanel::Slot(0, 1).ColumnSpan(2).Padding(5)
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Center)
			[
				SNew(SBox)
				.WidthOverride(200.0f)
			[
				SNew(SButton).ContentPadding(20)
				.Text(LOCTEXT("CapturePose", "捕获姿态"))
				]
			]
		+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Center)
			[
				SNew(SBox)
				.WidthOverride(200.0f)
				[
					SNew(SButton).ContentPadding(20)
					.Text(LOCTEXT("ClearPose", "清除姿态"))
				]
			]
		+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left)
			[
				SNew(SBox)
				.WidthOverride(100.0f)
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("CaptureStatus", "未捕获"))
				]
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
			SNew(SCheckBox)
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
				SNew(SCheckBox)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("WristTwist1", "手腕是否在中距离上有扭曲"))
				]
			]
		+ SVerticalBox::Slot()
			[
				SNew(SCheckBox)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("WristTwist2", "手腕是否伸展到或接近极限距离"))
				]
			]
		]
	+ SGridPanel::Slot(1, 4).Padding(5)
		[
			SNew(SCheckBox)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("WristMuscleCheckbox", "姿势是否主要是静态的（即保持> 1分钟），或者是否重复动作每分钟发生4次或更多。"))
			]
		]
	+SGridPanel::Slot(1,5).Padding(5)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			[
				SNew(SEditableTextBox)	
			]
			+SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("WeightUnit","kg"))
			]
		]
	+ SGridPanel::Slot(1, 6).Padding(5)
		[
			SNew(SCheckBox)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("TrunkMuscleCheckbox", "姿势是否主要是静态的（即保持> 1分钟），或者是否重复动作每分钟发生4次或更多。"))
			]
		]
	+SGridPanel::Slot(1,7).Padding(5)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			[
				SNew(SEditableTextBox)	
			]
			+SHorizontalBox::Slot()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("WeightUnit","kg"))
			]
		]
	+ SGridPanel::Slot(1, 10).HAlign(HAlign_Left).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("RI_Value", "2.0"))
		]
	+ SGridPanel::Slot(1, 11).HAlign(HAlign_Left).Padding(5)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("RULAScore_Value", "9.00"))
		]
	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE