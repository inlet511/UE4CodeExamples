// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Ergonomics.h"
#include "ErgonomicsStyle.h"
#include "ErgonomicsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName ErgonomicsTabName("Ergonomics");

#define LOCTEXT_NAMESPACE "FErgonomicsModule"

void FErgonomicsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FErgonomicsStyle::Initialize();
	FErgonomicsStyle::ReloadTextures();

	FErgonomicsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenNIOSHWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenREBAWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenRULAWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenWISHAWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenSnookWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FErgonomicsModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FErgonomicsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ErgonomicsTabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FErgonomicsTabTitle", "Ergonomics"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FErgonomicsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FErgonomicsStyle::Shutdown();

	FErgonomicsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ErgonomicsTabName);
}

TSharedRef<SDockTab> FErgonomicsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FErgonomicsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Ergonomics.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FErgonomicsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(ErgonomicsTabName);
}

void FErgonomicsModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FErgonomicsCommands::Get().OpenNIOSHWindow);
}

void FErgonomicsModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FErgonomicsCommands::Get().OpenNIOSHWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FErgonomicsModule, Ergonomics)