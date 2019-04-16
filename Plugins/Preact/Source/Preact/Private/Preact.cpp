// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Preact.h"
#include "PreactStyle.h"
#include "PreactCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName PreactTabName("Preact");

#define LOCTEXT_NAMESPACE "FPreactModule"

void FPreactModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPreactStyle::Initialize();
	FPreactStyle::ReloadTextures();

	FPreactCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPreactCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPreactModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FPreactModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FPreactModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PreactTabName, FOnSpawnTab::CreateRaw(this, &FPreactModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPreactTabTitle", "Preact"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPreactModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FPreactStyle::Shutdown();

	FPreactCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PreactTabName);
}

TSharedRef<SDockTab> FPreactModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPreactModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("Preact.cpp"))
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

void FPreactModule::PluginButtonClicked()
{
	UE_LOG(LogTemp,Warning,TEXT("HI!!!,%s"),*(GEditor->GetEditorWorldContext().World()->GetMapName()));
	FGlobalTabmanager::Get()->InvokeTab(PreactTabName);
}

void FPreactModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FPreactCommands::Get().OpenPluginWindow);
}

void FPreactModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FPreactCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPreactModule, Preact)