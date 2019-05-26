#include "TaskEditorSlate.h"
#include "SBox.h"
#include "SBorder.h"
#include "SBoxPanel.h"
#include "ModuleManager.h"
#include "PropertyEditorModule.h"

void STaskEditorSlate::Construct(const FArguments& InArgs)
{
	//�Ӵ���Ĳ����л�ȡTask����
	Task = InArgs._Task.Get();

	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//����DetailView
	FDetailsViewArgs DetailsViewArgs; 
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
