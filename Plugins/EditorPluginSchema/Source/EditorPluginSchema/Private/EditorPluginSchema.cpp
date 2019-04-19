// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorPluginSchema.h"

#include "EditorPluginSchemaCommands.h"
#include "EditorPluginSchemaStyle.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "LevelEditor.h"
#include "Misc/MessageDialog.h"
#include "SImage.h"

static const FName EditorPluginSchemaTabName("EditorPluginSchema");

#define LOCTEXT_NAMESPACE "FEditorPluginSchemaModule"

void FEditorPluginSchemaModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FEditorPluginSchemaStyle::Initialize();
	FEditorPluginSchemaStyle::ReloadTextures();

	FEditorPluginSchemaCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
	FEditorPluginSchemaCommands::Get().PluginAction,
	FExecuteAction::CreateRaw(this, &FEditorPluginSchemaModule::PluginButtonClicked),
	FCanExecuteAction());

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	//Menu 扩展菜单项
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FEditorPluginSchemaModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}

	//MenuBar 扩展菜单栏
	{
		TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender());
		MenuBarExtender->AddMenuBarExtension("Help", EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateRaw(this, &FEditorPluginSchemaModule::AddMenuBarExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);
	}

	//MenuBar 增加下拉菜单栏
	{
		TSharedPtr<FExtender> MenuBarExtender = MakeShareable(new FExtender());
		MenuBarExtender->AddMenuBarExtension("Help", EExtensionHook::After, PluginCommands, FMenuBarExtensionDelegate::CreateRaw(this, &FEditorPluginSchemaModule::AddMenuBarPulldown));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuBarExtender);
	}

	//增加工具栏项
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FEditorPluginSchemaModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	//增加选择物体后右键菜单
	{
		auto& AllSelectedObjsExtenderDelegates = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
		AllSelectedObjsExtenderDelegates.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(this, &FEditorPluginSchemaModule::SelectedActors));
		FLevelViewportMenuExtender_SelectedActors = AllSelectedObjsExtenderDelegates.Last().GetHandle();
	}
}

void FEditorPluginSchemaModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorPluginSchemaStyle::Shutdown();

	FEditorPluginSchemaCommands::Unregister();
}

void FEditorPluginSchemaModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
	LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	FText::FromString(TEXT("FEditorPluginSchemaModule::PluginButtonClicked()")),
	FText::FromString(TEXT("EditorPluginSchema.cpp")));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FEditorPluginSchemaModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.BeginSection(TEXT("SampleHookPoint"));
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.EndSection();
}

void FEditorPluginSchemaModule::AddMenuBarExtension(FMenuBarBuilder& Builder)
{
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
}

void FEditorPluginSchemaModule::AddMenuBarPulldown(FMenuBarBuilder& Builder)
{
	Builder.AddPullDownMenu(
		LOCTEXT("PullDownMenuName","SamplePullDown"),
		LOCTEXT("PullDownMenuTip","SampleTipsContent"),
		FNewMenuDelegate::CreateRaw(this,&FEditorPluginSchemaModule::PullDownBar),
		"PullDownHookPoint"
	);
}


void FEditorPluginSchemaModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	//Builder.AddToolBarButton(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddComboButton(
		FUIAction(),
		FOnGetContent::CreateStatic<TSharedPtr<FUICommandList>>(&FTestABC::MakeWidget,PluginCommands),
		LOCTEXT("AAA","AAA"),
		LOCTEXT("BBB","BBB"),
		FSlateIcon()
	);
}

void FEditorPluginSchemaModule::PullDownBar(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddMenuSeparator();
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddSubMenu(
		LOCTEXT("PullDownMenuName","SamplePullDown"),
		LOCTEXT("PullDownMenuTip","SampleTipsContent"),
		FNewMenuDelegate::CreateRaw(this,&FEditorPluginSchemaModule::SubMenuBar),
		"SubMenuHookPoint"
	);
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddWidget(
		SNew(SImage),
		LOCTEXT("ImageName","SampleImage")
	);
	Builder.AddEditableText(
		LOCTEXT("EditableTextField","EditableTextField"),
		LOCTEXT("EditableTextTips","EditableTextTips"),
		FSlateIcon(),
		LOCTEXT("DefaultText","DefaultText")
	);
	Builder.AddWrapperSubMenu(
		LOCTEXT("WrapperName","WrapperName"),
		LOCTEXT("WrapperTips","WrapperTips"),
		FOnGetContent::CreateStatic<TSharedPtr<FUICommandList>>(&FTestABC::MakeWidget,PluginCommands),
		FSlateIcon()
	);
}

void FEditorPluginSchemaModule::SubMenuBar(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddMenuSeparator();
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
}

TSharedRef<FExtender> FEditorPluginSchemaModule::SelectedActors(const TSharedRef<FUICommandList> MyUICommandList, const TArray<AActor*> AllActors)
{
	TSharedRef<FExtender> Extender = MakeShareable(new FExtender);
	if (AllActors.Num() > 0)
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		TSharedRef<FUICommandList> LevelCommand = LevelEditorModule.GetGlobalLevelEditorActions();

		Extender->AddMenuExtension("ActorControl", EExtensionHook::After, LevelCommand, FMenuExtensionDelegate::CreateRaw(this, &FEditorPluginSchemaModule::AddMenuExtension));

	}
	return Extender;
}

void FEditorPluginSchemaModule::AddContextMenuToSelectedObject(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FEditorPluginSchemaCommands::Get().PluginAction);
}

TSharedRef<SWidget> FTestABC::MakeWidget(TSharedPtr<class FUICommandList> PluginCommands)
{
	return SNew(SImage);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorPluginSchemaModule, EditorPluginSchema)