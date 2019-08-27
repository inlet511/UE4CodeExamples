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

static const FName NIOSHTabName("NOISH");
static const FName REBATabName("REBA");
static const FName RULATabName("RULA");
static const FName WISHATabName("WISHA");
static const FName SnookTabName("Snook");

#define LOCTEXT_NAMESPACE "FErgonomicsModule"

#define MAPACTION(Algorithm) \
PluginCommands->MapAction( \
	FErgonomicsCommands::Get().Open##Algorithm##Window,\
		FExecuteAction::CreateRaw(this, &FErgonomicsModule::PluginButtonClicked, ##Algorithm##TabName),\
		FCanExecuteAction());

#define REGISTER_TAB_SPAWNER(Algorithm) \
FGlobalTabmanager::Get()->RegisterNomadTabSpawner(Algorithm##TabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsModule::OnSpawnTab_##Algorithm##)) \
		.SetDisplayName(LOCTEXT("##Algorithm##TabNameTabTitle", "##Algorithm##")) \
		.SetMenuType(ETabSpawnerMenuType::Hidden);

void FErgonomicsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FErgonomicsStyle::Initialize();
	FErgonomicsStyle::ReloadTextures();

	FErgonomicsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	MAPACTION(NIOSH)
	MAPACTION(REBA)
	MAPACTION(RULA)
	MAPACTION(WISHA)
	MAPACTION(Snook)

		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	

	//添加ToolBar
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FErgonomicsModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	REGISTER_TAB_SPAWNER(NIOSH)
	REGISTER_TAB_SPAWNER(REBA)
	REGISTER_TAB_SPAWNER(RULA)
	REGISTER_TAB_SPAWNER(WISHA)
	REGISTER_TAB_SPAWNER(Snook)
}

void FErgonomicsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FErgonomicsStyle::Shutdown();

	FErgonomicsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NIOSHTabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(REBATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(RULATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WISHATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SnookTabName);
}

TSharedRef<SDockTab> FErgonomicsModule::OnSpawnTab_NIOSH(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Label(LOCTEXT("NIOSHTabTitle", "NIOSH"))
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
			.HAlign(HAlign_Fill)
			.VAlign(HAlign_Fill)
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
			.HAlign(HAlign_Fill)
			.VAlign(HAlign_Fill)
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
			.HAlign(HAlign_Fill)
			.VAlign(HAlign_Fill)
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