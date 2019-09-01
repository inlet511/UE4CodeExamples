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
#include "Engine/Selection.h"
#include "Editor.h"

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
				+ SGridPanel::Slot(0, 8).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Weight", "物体重量"))
					]
				+ SGridPanel::Slot(0, 9).HAlign(HAlign_Center).ColumnSpan(3).Padding(5,20,5,5)
					[
						SNew(SButton).ContentPadding(20)
						.OnClicked(this,&SNIOSHWidget::Evaluate)
						.Text(LOCTEXT("Evaluation", "评估"))
					]
				+SGridPanel::Slot(0,10)
					[
						SNew(SSpacer)
					]
				+ SGridPanel::Slot(0, 11).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RI_Label", "风险指数(RI)"))
					]
				+ SGridPanel::Slot(0, 12).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("RWL_Label", "建议重量限制(RWL,单位kg)"))
					]
				+ SGridPanel::Slot(0, 13).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HM_Label", "HM"))
					]
				+ SGridPanel::Slot(0, 14).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("VM_Label", "VM")) 
					]
				+ SGridPanel::Slot(0, 15).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("DM_Label", "DM"))
					]
				+ SGridPanel::Slot(0, 16).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("AM_Label", "AM"))
					]
				+ SGridPanel::Slot(0, 17).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("CM_Label", "CM"))
					]
				+ SGridPanel::Slot(0, 18).HAlign(HAlign_Right).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("FM_Label", "FM"))
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
						SAssignNew(Frequency_Input, SEditableTextBox)
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
				+ SGridPanel::Slot(1, 8).Padding(5)
					[
						SAssignNew(Weight_Input, SEditableTextBox)
					]
				+ SGridPanel::Slot(1, 11).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(RI,STextBlock)
						.Text(LOCTEXT("RI", "0.0"))
					]
				+ SGridPanel::Slot(1, 12).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(RWL,STextBlock)
						.Text(LOCTEXT("RWL", "0.0"))
					]
				+ SGridPanel::Slot(1, 13).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(HM,STextBlock)
						.Text(LOCTEXT("HM", "0.0"))
					]
				+ SGridPanel::Slot(1, 14).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(VM,STextBlock)
						.Text(LOCTEXT("VM", "0.0"))
					]
				+ SGridPanel::Slot(1, 15).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(DM,STextBlock)
						.Text(LOCTEXT("DM", "0.0"))
					]
				+ SGridPanel::Slot(1, 16).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(AM,STextBlock)
						.Text(LOCTEXT("AM", "0.0"))
					]
				+ SGridPanel::Slot(1, 17).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(CM,STextBlock)
						.Text(LOCTEXT("CM", "0.0"))
					]
				+ SGridPanel::Slot(1, 18).ColumnSpan(2).HAlign(HAlign_Center).Padding(5)
					[
						SAssignNew(FM,STextBlock)
						.Text(LOCTEXT("FM", "0.0"))
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
				+ SGridPanel::Slot(2, 8).HAlign(HAlign_Left).Padding(5)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("WeightUnit", "kg"))
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




FReply SNIOSHWidget::CaptureStart()
{
	USelection* selection = GEditor->GetSelectedActors();

	if (selection->Num() <= 0)
		return FReply::Unhandled();
	int32 idx = 0;
	for (idx = 0; idx < selection->Num()  ; idx++)
	{
		UObject * obj = selection->GetSelectedObject(idx);
		AActor* TargetActor = Cast<AActor>(obj);
		if (TargetActor)
		{
			USkeletalMeshComponent* skeletalMeshComp = TargetActor->FindComponentByClass<USkeletalMeshComponent>();
			if (skeletalMeshComp)
			{
				EditingNIOSH->Skeleton = skeletalMeshComp;
				EditingNIOSH->SnapshotStartPose();

				HorizontalPos_Start->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->StartHLocation)));
				VerticalPos_Start->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->StartVLocation)));
				Asymmetric_Start->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->StartAsymmetryAngle)));

				return FReply::Handled();
			}
		}
	}

	return FReply::Unhandled();
}

FReply SNIOSHWidget::CaptureEnd()
{
	USelection* selection = GEditor->GetSelectedActors();

	if (selection->Num() <= 0)
		return FReply::Unhandled();

	for (int i = 0; i < selection->Num() ; i++)
	{
		UObject * obj = selection->GetSelectedObject(i);
		AActor* TargetActor = Cast<AActor>(obj);
		if (TargetActor)
		{
			USkeletalMeshComponent* skeletalMeshComp = TargetActor->FindComponentByClass<USkeletalMeshComponent>();
			if (skeletalMeshComp)
			{
				EditingNIOSH->Skeleton = skeletalMeshComp;
				EditingNIOSH->SnapshotEndPose();

				HorizontalPos_End->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->EndHLocation)));
				VerticalPos_End->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->EndVLocation)));
				Asymmetric_End->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->EndAsymmetryAngle)));

				return FReply::Handled();
			}
		}
	}

	return FReply::Unhandled();
}

FReply SNIOSHWidget::Evaluate()
{
	EditingNIOSH->Calculate();
	
	RI->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->RI)));
	RWL->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->RWL)));
	HM->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->HM)));
	VM->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->VM)));
	DM->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->DM)));
	AM->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->AM)));
	CM->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->CM)));
	FM->SetText(FText::FromString(FString::SanitizeFloat(EditingNIOSH->FM)));
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE