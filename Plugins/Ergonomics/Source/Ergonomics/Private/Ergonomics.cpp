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

static const FName NOISHTabName("NOISH");
static const FName REBATabName("REBA");
static const FName RULATabName("RULA");
static const FName WISHATabName("WISHA");
static const FName SnookTabName("Snook");

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
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked, NOISHTabName),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenREBAWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked, REBATabName),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenRULAWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked, RULATabName),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenWISHAWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked, WISHATabName),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FErgonomicsCommands::Get().OpenSnookWindow,
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked, SnookTabName),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	

	//添加ToolBar
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FErgonomicsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NOISHTabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnTab_NIOSH))
		.SetDisplayName(LOCTEXT("NOISHTabNameTabTitle", "NOISH"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(REBATabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnTab_REBA))
		.SetDisplayName(LOCTEXT("REBATabTitle", "REBA"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(RULATabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnTab_RULA))
		.SetDisplayName(LOCTEXT("RULATabTitle", "RULA"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(WISHATabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnTab_WISHA))
		.SetDisplayName(LOCTEXT("WISHATabTitle", "WISHA"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SnookTabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnTab_Snook))
		.SetDisplayName(LOCTEXT("SnookTabTitle", "Snook"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FErgonomicsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FErgonomicsStyle::Shutdown();

	FErgonomicsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NOISHTabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(REBATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(RULATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WISHATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SnookTabName);
}

TSharedRef<SDockTab> FErgonomicsModule::OnSpawnTab_NIOSH(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(LOCTEXT("NOISHTabTitle", "NOISH"))
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
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
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
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

void FErgonomicsModule::PluginButtonClicked(const FName TabName)
{
	FGlobalTabmanager::Get()->InvokeTab(TabName);
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
		LOCTEXT("ErgonomicsTipsLabel", "人机工效分析工具集"),
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