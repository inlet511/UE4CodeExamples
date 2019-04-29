#include "SlateMain.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "MainSlate"

void SMainSlate::Construct(const FArguments & InArgs)
{

	CheckBoxArray.SetNum(4);
	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.Padding(10)
		.AutoHeight()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Padding(FMargin(0,0,4.0f,0))
				[
					SAssignNew(CheckBoxArray[0],SCheckBox)
					.OnCheckStateChanged(this, &SMainSlate::OnValChanged<0>)
					.ToolTipText(LOCTEXT("Lablel1","Label1"))
					.IsChecked(ECheckBoxState::Checked)
					.Content()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Text1","Text1"))
					]
				]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Padding(FMargin(0, 0, 4.0f, 0))
				[
					SAssignNew(CheckBoxArray[1], SCheckBox)
					.OnCheckStateChanged(this, &SMainSlate::OnValChanged<1>)
					.ToolTipText(LOCTEXT("Lablel2", "Label2"))
					.IsChecked(ECheckBoxState::Unchecked)
					.Content()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Text2", "Text2"))
					]
				]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Padding(FMargin(0, 0, 4.0f, 0))
				[
					SAssignNew(CheckBoxArray[2], SCheckBox)
					.OnCheckStateChanged(this, &SMainSlate::OnValChanged<2>)
					.ToolTipText(LOCTEXT("Lablel3", "Label3"))
					.IsChecked(ECheckBoxState::Unchecked)
					.Content()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Text3", "Text3"))
					]
				]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Padding(FMargin(0, 0, 4.0f, 0))
				[
					SAssignNew(CheckBoxArray[3], SCheckBox)
					.OnCheckStateChanged(this, &SMainSlate::OnValChanged<3>)
					.ToolTipText(LOCTEXT("Lablel4", "Label4"))
					.IsChecked(ECheckBoxState::Unchecked)
					.Content()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("Text4", "Text4"))
					]
				]
		]

	];
}

#undef LOCTEXT_NAMESPACE