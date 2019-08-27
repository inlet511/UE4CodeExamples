// Fill out your copyright notice in the Description page of Project Settings.


#include "SREBAWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "SGridPanel.h"
#include "STextBlock.h"
#include "SSpacer.h"
#include "Widgets/SBoxPanel.h"
#include "SEditableTextBox.h"
#include "SCheckBox.h"
#include "SBox.h"

#define LOCTEXT_NAMESPACE "SREBAWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SREBAWidget::Construct(const FArguments& InArgs)
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
			.Text(LOCTEXT("TitleLabel", "REBA(快速全身评估)"))
		]

		// Column 1
	+ SGridPanel::Slot(0, 1).ColumnSpan(2).Padding(5)
		[
			SNew(SHorizontalBox)

			+SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Center)
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
				.Text(LOCTEXT("Weight", "重量(kg)"))
			]
		+ SGridPanel::Slot(0, 3).HAlign(HAlign_Right).Padding(5)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ShockForce", "冲击力"))
			]
		+ SGridPanel::Slot(0, 4).HAlign(HAlign_Right).Padding(5)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Coupling", "耦合度"))
			]
		+ SGridPanel::Slot(0, 5).HAlign(HAlign_Right).Padding(5)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ActiveScore", "活动分数"))
			]
		+ SGridPanel::Slot(0, 6).HAlign(HAlign_Center).Padding(5)
			.ColumnSpan(2)
			[
				SNew(SButton)
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
		+ SGridPanel::Slot(0, 9).HAlign(HAlign_Right).Padding(5)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("REBAScore", "REBA分数"))
			]


		// Column 2
		+SGridPanel::Slot(1, 2).Padding(5).HAlign(HAlign_Left)
			[
				SNew(SBox).WidthOverride(300.0f)
				[					
					SNew(SEditableTextBox)
				]
			]
		+ SGridPanel::Slot(1, 3).Padding(5)
			[
				SNew(SCheckBox)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("ShockForceCheckbox", "是否存在冲击力，快速积聚力或突然用力"))
				]
			]
		+ SGridPanel::Slot(1, 4).Padding(5)
			[
				SNew(SVerticalBox)
					+ SVerticalBox::Slot().Padding(0, 0, 0, 10)
						[
							SNew(SCheckBox)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("Coupling1", "具有舒适的把手，或可以轻松地握住物体"))
							]
						]
					+ SVerticalBox::Slot().Padding(0, 0, 0, 10)
						[
							SNew(SCheckBox)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("Coupling2", "具有普通把手，或手可以握住物体。"))
							]
						]
					+ SVerticalBox::Slot().Padding(0)
						[
							SNew(SCheckBox)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("Coupling3", "没有把手，或握住物体困难。"))
							]
			]
		]
		+ SGridPanel::Slot(1,5).Padding(5)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().Padding(0, 0, 0, 10)
				[
					SNew(SCheckBox)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("ActiveScore1", "是否有身体部位静止超过一分钟"))
					]
				]
				+ SVerticalBox::Slot().Padding(0, 0, 0, 10)
					[
						SNew(SCheckBox)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ActiveScore2", "是否有重复的范围动作（超过4次/分钟）"))
						]
					]
				+ SVerticalBox::Slot().Padding(0)
					[
						SNew(SCheckBox)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ActiveScore3", "是否有会导致姿势大范围变化的动作"))
						]
					]
			]
		+ SGridPanel::Slot(1, 8).HAlign(HAlign_Left).Padding(5)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("RI_Value", "2.0"))
			]
		+ SGridPanel::Slot(1, 9).HAlign(HAlign_Left).Padding(5)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("REBAScore_Value", "9.00"))
			]

	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE