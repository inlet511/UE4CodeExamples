// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureToolEdModeToolkit.h"
#include "MeasureToolEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"
#include "CommonStructures.h"
#include "Private/Framework/MultiBox/SEditableTextBlock.h"
#include "ObjectRulerTool.h"
#include "AnnotationTool.h"



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


			//1. 顶部标签按钮
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
					.ContentPadding(10.0f)
					.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::SetCurrentMeasureTool,EMeasureTool::POINT_RULER_TOOL)
					.IsEnabled_Raw(this,&FMeasureToolEdModeToolkit::ToolButtonActive,EMeasureTool::POINT_RULER_TOOL)
				]

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Bottom)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("ObjectMeasureLabel", "物体间距测量"))
					.ContentPadding(10.0f)
					.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::SetCurrentMeasureTool,EMeasureTool::OBJECT_RULER_TOOL)
					.IsEnabled_Raw(this,&FMeasureToolEdModeToolkit::ToolButtonActive,EMeasureTool::OBJECT_RULER_TOOL)
				]

				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Bottom)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("AnnotationLabel", "标注"))
					.ContentPadding(10.0f)
					.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::SetCurrentMeasureTool,EMeasureTool::ANNOTATION_TOOL)
					.IsEnabled_Raw(this,&FMeasureToolEdModeToolkit::ToolButtonActive,EMeasureTool::ANNOTATION_TOOL)
				]
			]
			

			//2.1 点测量面板
			+ SVerticalBox::Slot()
			.Padding(0)
			.HAlign(HAlign_Fill)
			.FillHeight(5.0f)
			[
				SNew(SBorder)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.Padding(20.0f)
				.Visibility_Raw(this,&FMeasureToolEdModeToolkit::IsCurrentTool,EMeasureTool::POINT_RULER_TOOL)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("PointMeasureTips","依次点击两个顶点即可创建测量"))
				]
			]


			//2.2 物体测量面板
			+ SVerticalBox::Slot()
			.Padding(0)
			.HAlign(HAlign_Fill)
			.FillHeight(5.0f)
			[
				SNew(SBorder)
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Fill)
				.Padding(20.0f)
				.Visibility_Raw(this,&FMeasureToolEdModeToolkit::IsCurrentTool,EMeasureTool::OBJECT_RULER_TOOL)
				[
					SNew(SVerticalBox)

					+SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Fill)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("ObjectMeasureTips","请选择两个物体，并点击添加测量按钮"))
					]

					+SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Center)
					.Padding(0,20)
					.AutoHeight()
					[
						SNew(SButton)
						.ContentPadding(20.0f)
						.Text(LOCTEXT("AddMeasureButton","添加测量"))
						.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::AddMeasure)
						.IsEnabled_Raw(this,&FMeasureToolEdModeToolkit::SelectedNActors,2)
					]

				]
			]

			//2.3 标注面板
			+ SVerticalBox::Slot()
			.Padding(0)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			.FillHeight(5.0f)
			[
				SNew(SBorder)
				.VAlign(VAlign_Fill)
				.HAlign(HAlign_Fill)
				.Padding(20.0f)
				.Visibility_Raw(this,&FMeasureToolEdModeToolkit::IsCurrentTool,EMeasureTool::ANNOTATION_TOOL)
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AnnotationTips", "选择一个物体，并添加标注"))
					]

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.AutoHeight()
					.Padding(0, 10.0f)
					[
						SAssignNew(AnnotationInput, SEditableTextBox)
						.Padding(20)						
						.ForegroundColor(FLinearColor(0,1,0,1))
						.BackgroundColor(FLinearColor(0.1,0.1,0.1,1))
						.IsEnabled_Raw(this,&FMeasureToolEdModeToolkit::SelectedNActors,1)
					]

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Center)
					.AutoHeight()
					.Padding(0, 10.0f)
					[
						SNew(SButton)
						.ContentPadding(20.0f)
						.Text(LOCTEXT("AddAnnotationButton", "添加标注"))
						.IsEnabled_Raw(this,&FMeasureToolEdModeToolkit::SelectedNActors,1)
						.OnClicked_Raw(this,&FMeasureToolEdModeToolkit::AddAnnotation)
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

FReply FMeasureToolEdModeToolkit::AddAnnotation()
{
	FText AnnoText = AnnotationInput->GetText();
	MeasureEdMode->AnnotationTool->AddAnnotation(AnnoText);
	return FReply::Handled();
}

EVisibility FMeasureToolEdModeToolkit::IsCurrentTool(EMeasureTool InMeasureTool) const
{
	if (MeasureEdMode->GetCurrentMeasureMode() == InMeasureTool)
		return EVisibility::Visible;
	else
		return EVisibility::Collapsed;
}

bool FMeasureToolEdModeToolkit::ToolButtonActive(EMeasureTool InMeasureTool) const
{
	if (MeasureEdMode->GetCurrentMeasureMode() == InMeasureTool)
		return false;
	else 
		return true;
}

bool FMeasureToolEdModeToolkit::SelectedNActors(int32 n) const
{
	if (GEditor->GetSelectedActors()->Num() == n)
		return true;
	else 
		return false;
}

FReply FMeasureToolEdModeToolkit::AddMeasure()
{
	MeasureEdMode->ObjectRuler->AddMeasure();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
