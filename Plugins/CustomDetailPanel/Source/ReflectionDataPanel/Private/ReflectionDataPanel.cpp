// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ReflectionDataPanel.h"
#include "ReflectionDataPanelStyle.h"
#include "ReflectionDataPanelCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "CustomWidget.h"
#include "CustomObject.h"

static const FName ReflectionDataPanelTabName("ReflectionDataPanel");

#define LOCTEXT_NAMESPACE "FReflectionDataPanelModule"

void FReflectionDataPanelModule::StartupModule()
{
	//出于测试目的，在本模块初始化时构造一个CustomObject实例。
	CustomObject = NewObject<UCustomObject>();
	if (CustomObject)
	{
		CustomObject->AddToRoot();
	}

	FReflectionDataPanelStyle::Initialize();
	FReflectionDataPanelStyle::ReloadTextures();

	FReflectionDataPanelCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FReflectionDataPanelCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FReflectionDataPanelModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FReflectionDataPanelModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FReflectionDataPanelModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ReflectionDataPanelTabName, FOnSpawnTab::CreateRaw(this, &FReflectionDataPanelModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FReflectionDataPanelTabTitle", "ReflectionDataPanel"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FReflectionDataPanelModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FReflectionDataPanelStyle::Shutdown();

	FReflectionDataPanelCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ReflectionDataPanelTabName);

	if (CustomObject)
	{
		CustomObject->ConditionalBeginDestroy();
		CustomObject = nullptr;
	}
}

TSharedRef<SDockTab> FReflectionDataPanelModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SCustomWidget)
				.CustomObject(CustomObject)
			]
		];
}

void FReflectionDataPanelModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(ReflectionDataPanelTabName);
}

void FReflectionDataPanelModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FReflectionDataPanelCommands::Get().OpenPluginWindow);
}

void FReflectionDataPanelModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FReflectionDataPanelCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FReflectionDataPanelModule, ReflectionDataPanel)