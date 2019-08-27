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

#define LOCTEXT_NAMESPACE "SNIOSHWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SNIOSHWidget::Construct(const FArguments& InArgs)
{
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
						SNew(SButton).ContentPadding(5)
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
						.Text(LOCTEXT("CaptureStart", "捕获起点姿态"))
					]

				+ SGridPanel::Slot(1, 2).Padding(5)
					[
						SNew(SEditableTextBox)
					]
				+ SGridPanel::Slot(1, 3).Padding(5)
					[
						SNew(SEditableTextBox)
					]
				+ SGridPanel::Slot(1, 4).Padding(5)
					[
						SNew(SEditableTextBox)
					]

				+ SGridPanel::Slot(1, 5).Padding(5).ColumnSpan(2)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().Padding(0,0,0,10)
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
				+ SGridPanel::Slot(1, 6).Padding(5)
					[
						SNew(SEditableTextBox)
					]
				+ SGridPanel::Slot(1, 7).Padding(5).ColumnSpan(2)
					[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot().HAlign(HAlign_Left).Padding(10,0)
							[
								SNew(SCheckBox)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("DurationCheckBox1", "1小时"))
								]
							]
						+ SHorizontalBox::Slot().HAlign(HAlign_Left).Padding(10, 0)
							[
								SNew(SCheckBox)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("DurationCheckBox2", "1-2小时"))
								]
							]
						+ SHorizontalBox::Slot().HAlign(HAlign_Left).Padding(10, 0)
							[
								SNew(SCheckBox)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("DurationCheckBox3", "2-8小时"))
								]
							]
					]
				+ SGridPanel::Slot(1, 9).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("StartSpot", "起点"))
					]
				+ SGridPanel::Slot(1, 10).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RI_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 11).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RWL_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 12).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 13).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("VM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 14).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("DM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 15).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 16).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("CM_Start", "0.0"))
					]
				+ SGridPanel::Slot(1, 17).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("FM_Start", "0.0"))
					]

				// Column 3
				+ SGridPanel::Slot(2, 1).HAlign(HAlign_Center).Padding(5)
					[
						SNew(SButton)
						.Text(LOCTEXT("CaptureEnd", "捕获终点姿态"))
					]
				+ SGridPanel::Slot(2, 2).HAlign(HAlign_Fill).Padding(5)
					[
						SNew(SEditableTextBox)
					]
				+ SGridPanel::Slot(2, 3).HAlign(HAlign_Fill).Padding(5)
					[
						SNew(SEditableTextBox)
					]
				+ SGridPanel::Slot(2, 4).HAlign(HAlign_Fill).Padding(5)
					[
						SNew(SEditableTextBox)
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
						SNew(STextBlock)
						.Text(LOCTEXT("RI_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 11).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RWL_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 12).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 13).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("VM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 14).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("DM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 15).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 16).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("CM_End", "0.0"))
					]
				+ SGridPanel::Slot(2, 17).HAlign(HAlign_Center).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("FM_End", "0.0"))
					]
			
		];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE