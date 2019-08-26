// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Ergonomics.h"
#include "ErgonomicsStyle.h"
#include "ErgonomicsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "SNIOSHWidget.h"
#include "SREBAWidget.h"
#include "SRULAWidget.h"
#include "SWISHAWidget.h"
#include "SSnookWidget.h"

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
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FErgonomicsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ErgonomicsTabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnTab_NIOSH))
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

TSharedRef<SDockTab> FErgonomicsModule::OnSpawnTab_NIOSH(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SNIOSHWidget)
			]
		];
}


TSharedRef<class SDockTab> FErgonomicsModule::OnSpawnTab_REBA(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SREBAWidget)
			]
		];
}

TSharedRef<class SDockTab> FErgonomicsModule::OnSpawnTab_RULA(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SRULAWidget)

			]
		];
}

TSharedRef<class SDockTab> FErgonomicsModule::OnSpawnTab_WISHA(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SWISHAWidget)
			]
		];
}

TSharedRef<class SDockTab> FErgonomicsModule::OnSpawnTab_Snook(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[

			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SSnookWidget)
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
	Builder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateStatic(&FErgonomicsModule::GenerateErgonomicsToolBarMenu,PluginCommands.ToSharedRef()),
		LOCTEXT("ErgonomicsLabel", "人机工效分析"),
		LOCTEXT("ErgonomicsTipsLabel", "打开人机工效分析下拉菜单"),
		FSlateIcon(),
		false
	);
}

TSharedRef<SWidget> FErgonomicsModule::GenerateErgonomicsToolBarMenu(TSharedRef<class FUICommandList> InCommandList)
{
	const bool bShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, InCommandList);

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("AlgorithmLabel", "人机工效算法"));
	{
		MenuBuilder.AddMenuEntry(FErgonomicsCommands::Get().OpenNIOSHWindow);
		MenuBuilder.AddMenuEntry(FErgonomicsCommands::Get().OpenREBAWindow);
		MenuBuilder.AddMenuEntry(FErgonomicsCommands::Get().OpenRULAWindow);
		MenuBuilder.AddMenuEntry(FErgonomicsCommands::Get().OpenWISHAWindow);
		MenuBuilder.AddMenuEntry(FErgonomicsCommands::Get().OpenSnookWindow);

	}
	MenuBuilder.EndSection();
	return MenuBuilder.MakeWidget();
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FErgonomicsModule, Ergonomics)