#include "TaskEditorSlate.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

void STaskEditorSlate::Construct(const FArguments& InArgs)
{
	//�Ӵ���Ĳ����л�ȡTask����
	Task = InArgs._Task.Get();

	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//����DetailView
	FDetailsViewArgs DetailsViewArgs; 
	DetailsViewArgs.bShowScrollBar = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	DetailView = PropertyModule.CreateDetailView(DetailsViewArgs);
	DetailView->SetObject(Task,true);

	//ʵ��UI
	ChildSlot
		[
			SNew(SVerticalBox) 
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBox)
				.WidthOverride(300)
				.MinDesiredWidth(300)
				.MaxDesiredWidth(300)
					[
						SNew(SBorder)
						[
							DetailView.ToSharedRef()
						]
					]
			]
		];
}
