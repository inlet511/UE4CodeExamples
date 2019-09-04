// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ErgonomicsEditor.h"
#include "ErgonomicsEditorCommands.h"
#include "ErgonomicsEditorStyle.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "LevelEditor.h"
#include "SNIOSHWidget.h"
#include "SREBAWidget.h"
#include "SRULAWidget.h"
#include "SSnookWidget.h"
#include "SWISHAWidget.h"

#include "NIOSH.h"
#include "WISHA.h"
#include "REBA.h"
#include "RULA.h"
#include "Snook.h"


static const FName NIOSHTabName("NOISH");
static const FName REBATabName("REBA");
static const FName RULATabName("RULA");
static const FName WISHATabName("WISHA");
static const FName SnookTabName("Snook");

#define LOCTEXT_NAMESPACE "FErgonomicsEditorModule"

#define MAPACTION(Algorithm) \
PluginCommands->MapAction( \
	FErgonomicsEditorCommands::Get().Open##Algorithm##Window,\
		FExecuteAction::CreateRaw(this, &FErgonomicsEditorModule::PluginButtonClicked, ##Algorithm##TabName),\
		FCanExecuteAction());

#define REGISTER_TAB_SPAWNER(Algorithm) \
FGlobalTabmanager::Get()->RegisterNomadTabSpawner(Algorithm##TabName, FOnSpawnTab::CreateRaw(this, &FErgonomicsEditorModule::OnSpawnTab_##Algorithm##)) \
		.SetDisplayName(LOCTEXT(#Algorithm"TabNameTabTitle", #Algorithm)) \
		.SetMenuType(ETabSpawnerMenuType::Hidden);

void FErgonomicsEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FErgonomicsEditorStyle::Initialize();
	FErgonomicsEditorStyle::ReloadTextures();

	FErgonomicsEditorCommands::Register();

	//初始化算法对象
	InitAlgorithmObject();


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
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FErgonomicsEditorModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	REGISTER_TAB_SPAWNER(NIOSH)
	REGISTER_TAB_SPAWNER(REBA)
	REGISTER_TAB_SPAWNER(RULA)
	REGISTER_TAB_SPAWNER(WISHA)
	REGISTER_TAB_SPAWNER(Snook)
}

void FErgonomicsEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FErgonomicsEditorStyle::Shutdown();

	FErgonomicsEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NIOSHTabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(REBATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(RULATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WISHATabName);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SnookTabName);
}

TSharedRef<SDockTab> FErgonomicsEditorModule::OnSpawnTab_NIOSH(const FSpawnTabArgs& SpawnTabArgs)
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


TSharedRef<class SDockTab> FErgonomicsEditorModule::OnSpawnTab_REBA(const class FSpawnTabArgs& SpawnTabArgs)
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

TSharedRef<class SDockTab> FErgonomicsEditorModule::OnSpawnTab_RULA(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SRULAWidget)

			]
		];
}

TSharedRef<class SDockTab> FErgonomicsEditorModule::OnSpawnTab_WISHA(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SWISHAWidget)
			]
		];
}

TSharedRef<class SDockTab> FErgonomicsEditorModule::OnSpawnTab_Snook(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[

			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SSnookWidget)
			]
		];
}

void FErgonomicsEditorModule::PluginButtonClicked(const FName TabName)
{
	FGlobalTabmanager::Get()->InvokeTab(TabName);
}

void FErgonomicsEditorModule::InitAlgorithmObject()
{
	EditingNIOSH = MakeShareable(new NIOSH());
	EditingREBA = MakeShareable(new REBA());
	EditingRULA = MakeShareable(new RULA());
	EidtingWISHA = MakeShareable(new WISHA());
	EditingSnook = MakeShareable(new Snook());
}

void FErgonomicsEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FErgonomicsEditorCommands::Get().OpenNIOSHWindow);
}

void FErgonomicsEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateStatic(&FErgonomicsEditorModule::GenerateErgonomicsToolBarMenu,PluginCommands.ToSharedRef()),
		LOCTEXT("ErgonomicsLabel", "人机工效分析"),
		LOCTEXT("ErgonomicsTipsLabel", "人机工效分析工具集"),
		FSlateIcon(),
		false
	);
}

TSharedRef<SWidget> FErgonomicsEditorModule::GenerateErgonomicsToolBarMenu(TSharedRef<class FUICommandList> InCommandList)
{
	const bool bShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, InCommandList);

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("AlgorithmLabel", "人机工效算法"));
	{
		MenuBuilder.AddMenuEntry(FErgonomicsEditorCommands::Get().OpenNIOSHWindow);
		MenuBuilder.AddMenuEntry(FErgonomicsEditorCommands::Get().OpenREBAWindow);
		MenuBuilder.AddMenuEntry(FErgonomicsEditorCommands::Get().OpenRULAWindow);
		MenuBuilder.AddMenuEntry(FErgonomicsEditorCommands::Get().OpenWISHAWindow);
		//MenuBuilder.AddMenuEntry(FErgonomicsEditorCommands::Get().OpenSnookWindow);
	}
	MenuBuilder.EndSection();
	return MenuBuilder.MakeWidget();
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FErgonomicsEditorModule, ErgonomicsEditor)