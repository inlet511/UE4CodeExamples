#include "ContingencyPlanEditor.h"
#include "ContingencyPlanEditorStyle.h"
#include "ContingencyPlanEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"
#include "TaskActions.h"
#include "TaskFactory.h"

static const FName ContingencyPlanEditorTabName("ContingencyPlanEditor");


#define LOCTEXT_NAMESPACE "FContingencyPlanEditorModule"

void FContingencyPlanEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FContingencyPlanEditorStyle::Initialize();
	FContingencyPlanEditorStyle::ReloadTextures();

	FContingencyPlanEditorCommands::Register();



	//注册AssetTypeAction
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	ContingencyCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("ContingencyCategory")), LOCTEXT("ContingencyCategory", "ContingencyCategory"));
	RegisteredAssetTypeActions.Add(MakeShareable(new FTaskActions()));
	AssetTools.RegisterAssetTypeActions(RegisteredAssetTypeActions[RegisteredAssetTypeActions.Num() - 1]);



	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FContingencyPlanEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FContingencyPlanEditorModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FContingencyPlanEditorModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FContingencyPlanEditorModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FContingencyPlanEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();
		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}


	FContingencyPlanEditorStyle::Shutdown();

	FContingencyPlanEditorCommands::Unregister();
}

void FContingencyPlanEditorModule::PluginButtonClicked()
{
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FContingencyPlanEditorModule::PluginButtonClicked()")),
							FText::FromString(TEXT("ContingencyPlanEditor.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FContingencyPlanEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FContingencyPlanEditorCommands::Get().PluginAction);
}

void FContingencyPlanEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FContingencyPlanEditorCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FContingencyPlanEditorModule, ContingencyPlanEditor)