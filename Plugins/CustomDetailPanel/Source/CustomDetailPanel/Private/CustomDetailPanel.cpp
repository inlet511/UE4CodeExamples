// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CustomDetailPanel.h"

#include "MyTestDetailCustomization.h"
#include "PropertyEditorModule.h"
#include "StructVariableDetail.h"

#define LOCTEXT_NAMESPACE "FCustomDetailPanelModule"

void FCustomDetailPanelModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");


	//注册对象自定义 Register Object Customization
	FName ObjectClassName = FName(TEXT("CustomObject"));
	PropertyModule.RegisterCustomClassLayout(ObjectClassName, FOnGetDetailCustomizationInstance::CreateStatic(&FMyTestDetailCustomization::MakeInstance));
	RegisteredClassNames.Add(ObjectClassName);

	//注册PropertyTypeCustomization
	FName StructName = FName(TEXT("StructVariable"));
	PropertyModule.RegisterCustomPropertyTypeLayout(StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FStructVariableDetail::MakeInstance));
	RegisteredPropertyTypes.Add(StructName);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FCustomDetailPanelModule::ShutdownModule()
{
	//模块关闭时要注销已经注册的自定义

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		for (auto It = RegisteredClassNames.CreateConstIterator(); It; ++It)
		{
			if (It->IsValid())
			{
				PropertyModule.UnregisterCustomClassLayout(*It);
			}
		}

		for (auto It = RegisteredPropertyTypes.CreateConstIterator(); It; ++It)
		{
			if (It->IsValid())
			{
				PropertyModule.UnregisterCustomPropertyTypeLayout(*It);
			}
		}

		PropertyModule.NotifyCustomizationModuleChanged();
	}
}




#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomDetailPanelModule, CustomDetailPanel)