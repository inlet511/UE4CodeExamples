// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ContigencyPlanEditor.h"
#include "ContigencyPlanEditorStyle.h"
#include "ContigencyPlanEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"
#include "TaskActions.h"

static const FName ContigencyPlanEditorTabName("ContigencyPlanEditor");

#define LOCTEXT_NAMESPACE "FContigencyPlanEditorModule"

void FContigencyPlanEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FContigencyPlanEditorStyle::Initialize();
	FContigencyPlanEditorStyle::ReloadTextures();

	FContigencyPlanEditorCommands::Register();

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisteredAssetTypeActions.Add(MakeShareable(new FTaskActions()));
	AssetTools.RegisterAssetTypeActions(RegisteredAssetTypeActions[RegisteredAssetTypeActions.Num() - 1]);

	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FContigencyPlanEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FContigencyPlanEditorModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FContigencyPlanEditorModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FContigencyPlanEditorModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FContigencyPlanEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();
		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}


	FContigencyPlanEditorStyle::Shutdown();

	FContigencyPlanEditorCommands::Unregister();
}

void FContigencyPlanEditorModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FContigencyPlanEditorModule::PluginButtonClicked()")),
							FText::FromString(TEXT("ContigencyPlanEditor.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FContigencyPlanEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FContigencyPlanEditorCommands::Get().PluginAction);
}

void FContigencyPlanEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FContigencyPlanEditorCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FContigencyPlanEditorModule, ContigencyPlanEditor)