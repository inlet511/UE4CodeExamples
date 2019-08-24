// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureToolEdModeToolkit.h"
#include "MeasureToolEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"
#include "CommonStructures.h"
#include "Private/Framework/MultiBox/SEditableTextBlock.h"



#define LOCTEXT_NAMESPACE "FMeasureToolEdModeToolkit"

FMeasureToolEdModeToolkit::FMeasureToolEdModeToolkit()
{
}

void FMeasureToolEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	MeasureEdMode = (FMeasureToolEdMode*)GetEditorMode();
	if (MeasureEdMode == nullptr)
		return;

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Fill)
		.Padding(0)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.Padding(20.0f,0)
			.HAlign(HAlign_Fill)
			.FillHeight(0.5f)
			
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Bottom)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("PointMeasureLabel","选点测量"))
					.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::SetCurrentMeasureTool,EMeasureTool::POINT_RULER_TOOL)
				]

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Bottom)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("ObjectMeasureLabel", "物体间距测量"))
					.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::SetCurrentMeasureTool,EMeasureTool::OBJECT_RULER_TOOL)
				]

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Bottom)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("AnnotationLabel", "标注"))
				]
			]

			+ SVerticalBox::Slot()
			.Padding(0)
			.HAlign(HAlign_Fill)
			.FillHeight(5.0f)
			[
				SNew(SBorder)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.Padding(20.0f)
				.BorderImage(&brush1)
				.Visibility_Raw(this,&FMeasureToolEdModeToolkit::IsCurrentTool,EMeasureTool::POINT_RULER_TOOL)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("PointMeasureTips","依次点击两个顶点即可创建测量"))
				]
			]


			+ SVerticalBox::Slot()
			.Padding(0)
			.HAlign(HAlign_Fill)
			.FillHeight(5.0f)
			[
				SNew(SBorder)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.Padding(20.0f)
				.BorderImage(&brush2)
				.Visibility_Raw(this,&FMeasureToolEdModeToolkit::IsCurrentTool,EMeasureTool::OBJECT_RULER_TOOL)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.Padding(0,10.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("ObjectMeasureTips","请选择两个物体，并点击测量按钮"))
					]

					+SVerticalBox::Slot()
					.Padding(0,10.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("AddMeasureButton","添加测量"))
						.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::AddMeasure)
					]

				]
			]


			+ SVerticalBox::Slot()
			.Padding(0)
			.HAlign(HAlign_Fill)
			.FillHeight(5.0f)
			[
				SNew(SBorder)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.Padding(20.0f)
				.BorderImage(&brush3)
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.Padding(0, 10.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AnnotationTips", "选择一个物体，并添加标注"))
					]

					+ SVerticalBox::Slot()
					.Padding(0, 10.0f)
					[
						SAssignNew(AnnotationInput, SEditableTextBox)
						.ForegroundColor(FLinearColor(1,0,1,1))
						.BackgroundColor(FLinearColor(0,0,0,1))
					]

					+ SVerticalBox::Slot()
					.Padding(0, 10.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("AddAnnotationButton", "添加标注"))
					]

				]
			]
		];
	
	FModeToolkit::Init(InitToolkitHost);
}

FName FMeasureToolEdModeToolkit::GetToolkitFName() const
{
	return FName("MeasureToolEdMode");
}

FText FMeasureToolEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("MeasureToolEdModeToolkit", "DisplayName", "MeasureToolEdMode Tool");
}

class FEdMode* FMeasureToolEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FMeasureToolEdMode::EM_MeasureToolEdModeId);
}

FReply FMeasureToolEdModeToolkit::SetCurrentMeasureTool(EMeasureTool InMeasureTool)
{
	MeasureEdMode->SetCurrentMeasureMode(InMeasureTool);

	return FReply::Handled();
}

EVisibility FMeasureToolEdModeToolkit::IsCurrentTool(EMeasureTool InMeasureTool) const
{
	if (MeasureEdMode->GetCurrentMeasureMode() == InMeasureTool)
		return EVisibility::Visible;
	else
		return EVisibility::Collapsed;
}

FReply FMeasureToolEdModeToolkit::AddMeasure()
{
	MeasureEdMode->ObjectRuler->AddMeasure();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
