#include "CustomWidget.h"
#include "PropertyEditing.h"
#include "CustomObject.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"

void SCustomWidget::Construct(const FArguments& InArgs)
{
	CustomObject = InArgs._CustomObject;

	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;

	ConfigPanel = PropertyModule.CreateDetailView(DetailsViewArgs);
	//ConfigPanel->SetObject(UCustomObject::StaticClass()->GetDefaultObject(true), true);
	ConfigPanel->SetObject(CustomObject.Get());

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.WidthOverride(300)
			.MinDesiredWidth(300)
			.MaxDesiredWidth(300)
			[
				SNew(SBorder)
				[
					ConfigPanel.ToSharedRef()
				]
			]
		]
	];
}
